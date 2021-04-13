/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package replfiledemo;

import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

/**
 *
 * @author Marco
 */
public class ReplFileDemo
{
    static boolean debug = false;
    static String memphisURL = "http://localhost:8080/ReplicationManager/";
    static String memphisUser = "admin";
    static String memphisPassword = "ADMIN";
    static String primaryDbeName = "FAIRCOMS";
    static String secondaryDbeName = "FAIRCOM2";
    static String dbName = "ctreeSQL";
    static String planName = "ReplPlan1";
    // set primaryFileDir to the directory of the files to be replicated
    static String primaryFileDir = null; // default to LOCAL_DIRECTORY
    //static String primaryFileDir = "R:/data"; // JSON doesn't support backslash
    static List<String> primaryFileNames = Arrays.asList("custmast.dat","custordr.dat","itemmast.dat","ordritem.dat");
    // set secondaryFileDir to the directory of the replicated files
    static String secondaryFileDir = null; // default to LOCAL_DIRECTORY
    //static String secondaryFileDir = "R:/datarepl"; // JSON doesn't support backslash
    
    public static class DBEngine
    {
        private Object Id;
        HashMap<String,Object> databases = new HashMap<>();
        String localDir;
        Object opSystem;
        public DBEngine()
        {
            databases.clear();
        };
        public Object getId()
        {
            return Id;
        }
        public void setId(Object dbeId)
        {
            this.Id = dbeId;
        }
        public void setDatabases(JSONArray jsonDatabases)
        {
            for (int i = 0; i < jsonDatabases.size(); i++)
            {
                JSONObject db = (JSONObject) jsonDatabases.get(i);
                databases.put(db.get("name").toString(), db.get("id").toString());
            }
        }
        public Object getDatabaseId(String databaseName)
        {
            return databases.get(databaseName);
        }
        public void setLocalDir(String localDir)
        {
            this.localDir = localDir;
        }
        public String getLocalDir()
        {
            return this.localDir;
        }
        public void setOpSystem(Object opSystem)
        {
            this.opSystem = opSystem;
        }
        public Object getOpSystem()
        {
            return opSystem;
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
        throws Exception
    {
        if (args.length > 0)
        {
            if (args.length > 1)
            {
                if (args[1].equals("-debug"))
                    debug = true;
            }

            switch (args[0])
            {
                case "setup":
                    cleanup();
                    setup(planName, primaryDbeName, secondaryDbeName, primaryFileDir, primaryFileNames, secondaryFileDir);
                    break;
                case "cleanup":
                    cleanup();
                    break;
                case "start":
                    start(planName);
                    break;
                case "stop":
                    stop(planName);
                    break;
                case "redeploy":
                    redeploy(planName);
                    break;
                case "resync":
                    resync(planName, primaryFileNames);
                    break;
                case "status":
                    status(planName);
                    break;
                default:
                    System.err.println("Invalid argument.");
                    System.exit(1);
            }
        }
        else
        {
            System.err.println("Invalid argument.");
            System.exit(1);
        }
    }
    
    public static void cleanup()
        throws Exception
    {
        // connect to memphis server
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // remove all existing replication plans
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, null);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            ctMemphisStopReplPlan(memphisURL, token, jsonPlan.get("id").toString());
            ctMemphisRemoveReplPlan(memphisURL, token, jsonPlan.get("id").toString());
        }

        // remove all existing publications
        JSONArray jsonPubList = ctMemphisGetPublications(memphisURL, token, null);
        for (int i = 0; i < jsonPubList.size(); i++)
        {
            JSONObject jsonPub = (JSONObject) jsonPubList.get(i);

            ctMemphisRemovePublication(memphisURL, token, jsonPub.get("id").toString());
        }

        ctMemphisLogout(memphisURL, token);
    }
    
    public static void setup(String planName, String sourceDbeName, String targetDbeName, String sourceFileDir, List<String> sourceFileNames, String targetFileDir)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get list of available dbengines
        JSONArray jsonDbeList = ctMemphisGetDBEngines(memphisURL, token);

        // build a list of dbengines
        HashMap<String,DBEngine> dbeList = new HashMap<>();
        for (int i = 0; i < jsonDbeList.size(); i++)
        {
            JSONObject jsonDbe = (JSONObject) jsonDbeList.get(i);

            DBEngine dbe = new DBEngine();
            // get dbengine id and its databases
            dbe.setId(jsonDbe.get("id"));
            dbe.setDatabases(ctMemphisGetDatabases(memphisURL, token, jsonDbe.get("id")));

            String localDir = jsonDbe.get("localVolumeName").toString() + "/" + jsonDbe.get("localDir").toString();
            dbe.setLocalDir(localDir);
            
            dbe.setOpSystem(jsonDbe.get("opSystem"));

            dbeList.put(jsonDbe.get("name").toString(), dbe);
        }
        DBEngine sourceDbe = dbeList.get(sourceDbeName);
        DBEngine targetDbe = dbeList.get(targetDbeName);

        // get list of files on source
        if (sourceFileDir == null)
            sourceFileDir = sourceDbe.getLocalDir();
        if (targetFileDir == null)
            targetFileDir = targetDbe.getLocalDir();
        JSONArray fileList = new JSONArray();
        for (int i = 0; i < sourceFileNames.size(); i++)
        {
            JSONArray jsonFileList = ctMemphisGetFile(memphisURL, token,
                sourceFileDir + "/" + sourceFileNames.get(i),
                sourceDbe.getOpSystem());
            for (int j = 0; j < jsonFileList.size(); j++)
            {
                JSONObject jsonFile = (JSONObject) jsonFileList.get(j);
                JSONObject param = new JSONObject();
                param.put("file", jsonFile.get("id"));
                
                // begin of WORKAROUND CTREEACE-5994
                // ctMemphisGetFiles returns also directories
                if (jsonFile.get("isDir").equals(false))
                // end of WORKAROUND CTREEACE-5994

                fileList.add(param);
            }
        }

        // add publication to source dbengine
        String pubId = ctMemphisPersistPublication(memphisURL, token,
            "Publication1", null,
            sourceDbe.getId(),
            null);

        // add files to publication
        ctMemphisAddFilesToPublication(memphisURL, token, pubId, fileList);

        // add replication plan from source to target
        String planId = ctMemphisPersistReplPlan(memphisURL, token,
            planName,
            sourceDbe.getId(), targetDbe.getId(), 0);

        // subscribe publication to replication plan
        JSONObject param = (JSONObject) new JSONObject();
        param.put("sourcePath", sourceFileDir);
        param.put("targetPath", targetFileDir);
        JSONArray redirectionList = new JSONArray();
        redirectionList.add(param);
        ctMemphisPersistSubscription(memphisURL, token,
            "Subscription1", null,
            planId, pubId,
            targetDbe.getId(), null,
            redirectionList);

        // deploy replication
        ctMemphisDeployReplPlan(memphisURL, token, planId);

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    public static void start(String planName)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get replication plan by name
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, planName);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            // start replication plan
            ctMemphisStartReplPlan(memphisURL, token, jsonPlan.get("id").toString());
        }

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    public static void stop(String planName)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get replication plan by name
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, planName);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            // stop replication plan
            ctMemphisStopReplPlan(memphisURL, token, jsonPlan.get("id").toString());
        }

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    public static void status(String planName)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get replication plan by name
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, planName);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            // get status of replication plan
            String status = ctMemphisCheckReplPlanStatus(memphisURL, token, jsonPlan.get("id").toString());
            System.out.println("Replication is " + status);
        }

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    public static void redeploy(String planName)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get replication plan by name
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, planName);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            // redeploy all files in replication plan
            ctMemphisDeployReplPlan(memphisURL, token, jsonPlan.get("id").toString());
        }

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    public static void resync(String planName, List<String> fileNames)
        throws Exception
    {
        // connect to memphis
        String token = ctMemphisLogin(memphisURL, memphisUser, memphisPassword);

        // get replication plan by name
        JSONArray jsonPlanList = ctMemphisGetReplPlans(memphisURL, token, planName);
        for (int i = 0; i < jsonPlanList.size(); i++)
        {
            JSONObject jsonPlan = (JSONObject) jsonPlanList.get(i);

            JSONArray fileList = new JSONArray();
            // get publication by dbengine ID
            JSONArray jsonPubList = ctMemphisGetPublications(memphisURL, token, jsonPlan.get("sourceDBEngine"));
            for (int j = 0; j < jsonPubList.size(); j++)
            {
                JSONObject jsonPub = (JSONObject) jsonPubList.get(j);

                // get files in publication
                JSONArray jsonFileList = ctMemphisGetFilesFromPublication(memphisURL, token, jsonPub.get("id"));
                for (int k = 0; k < jsonFileList.size(); k++)
                {
                    JSONObject jsonFile = (JSONObject) jsonFileList.get(k);

                    // check that publication file is in resync file list
                    if (fileNames.contains(jsonFile.get("name").toString()))
                    {
                        JSONObject param = new JSONObject();
                        param.put("file", jsonFile.get("id"));
                        
                        // build resync file list
                        fileList.add(param);
                    }
                }
            }

            // resync files in replication plan
            ctMemphisResyncFiles(memphisURL, token, jsonPlan.get("id"), fileList);
        }

        // disconnect from memphis
        ctMemphisLogout(memphisURL, token);
    }
    
    private static String errorMessage(JSONObject error)
        throws Exception
    {
        String errorCode = error.get("errorCode").toString();
        String errorDesc = error.get("errorDesc").toString();

        return errorCode + " " + errorDesc;
    }

    private static String ctMemphisLogin(String url, String user, String password)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("user", user);
        param.put("password", password);

        JSONObject result = ctMemphis(url, "ctMemphisLogin", null, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return result.get("token").toString();
    }

    private static JSONArray ctMemphisGetDBEngines(String url, String token)
        throws Exception
    {
        JSONObject result = ctMemphis(url, "ctMemphisGetDBEngines", token, new JSONObject());
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("dbEngineList");
    }

    private static String ctMemphisCheckDBEngineStatus(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);

        JSONObject result = ctMemphis(url, "ctMemphisCheckDBEngineStatus", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        JSONArray statuses = (JSONArray) result.get("dbEngineStatusList");
        JSONObject status = (JSONObject) statuses.get(0);
        return status.get("status").toString();        
    }

    private static String ctMemphisCheckDBEngineConnection(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
        param.put("checkConnection", true);

        JSONObject result = ctMemphis(url, "ctMemphisCheckDBEngineStatus", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        JSONArray statuses = (JSONArray) result.get("dbEngineStatusList");
        JSONObject status = (JSONObject) statuses.get(0);
        return status.get("status").toString();        
    }

    private static JSONArray ctMemphisGetDatabases(String url, String token, Object dbEngine)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("dbEngine", dbEngine);

        JSONObject result = ctMemphis(url, "ctMemphisGetDatabases", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("databaseList");
    }

    private static String ctMemphisPersistPublication(String url, String token, String name, String description, Object dbEngine, Object database)
        throws Exception
    {
        JSONObject param = new JSONObject();
        JSONObject pub = new JSONObject();
        pub.put("name", name);
        pub.put("description", description);
        pub.put("dbEngine", dbEngine);
        if (database != null)
            pub.put("database", database);
        param.put("publication", pub);

        JSONObject result = ctMemphis(url, "ctMemphisPersistPublication", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return result.get("id").toString();
    }
    
    private static JSONArray ctMemphisGetFiles(String url, String token, Object database)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("database", database);

        JSONObject result = ctMemphis(url, "ctMemphisGetFiles", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("fileList");
    }

    private static JSONArray ctMemphisGetFile(String url, String token, Object filePath, Object opSystem)
        throws Exception
    {
        String path[] = new String[2];
        if (!filePath.toString().startsWith("/"))
        {
            path = filePath.toString().split(":");
            if (path[1].isEmpty())
            {
                throw new Exception("Not a full path directory!");
            }
        }
        else
        {
            path[0] = "";
            path[1] = filePath.toString();
        }
        String fileVolume = path[0];
        String fileDir = path[1].substring(1, path[1].lastIndexOf("/"));
        String fileName = path[1].substring(path[1].lastIndexOf("/")+1);

        JSONObject param = new JSONObject();
        param.put("opSystem", opSystem);
        param.put("name", fileVolume);

        JSONObject result = ctMemphis(url, "ctMemphisGetVolumes", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        JSONArray volumeList = (JSONArray) result.get("volumeList");
        if (volumeList.isEmpty())
        {
            throw new Exception("Path does not exist!");
        }
        JSONObject volume = (JSONObject) volumeList.get(0);
        
        param.clear();
        param.put("volume", volume.get("id"));
        param.put("path", fileDir);
        param.put("mask", fileName);
        param.put("ctreeOnly", true);
        param.put("refresh", true);
        param.put("recursive", false);

        result = ctMemphis(url, "ctMemphisGetFiles", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("fileList");
    }

    private static JSONArray ctMemphisGetFilesFromPublication(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);

        JSONObject result = ctMemphis(url, "ctMemphisGetFilesFromPublication", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("fileList");
    }

    private static void ctMemphisAddFilesToPublication(String url, String token, Object id, JSONArray fileList)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
        param.put("fileList", fileList);

        JSONObject result = ctMemphis(url, "ctMemphisAddFilesToPublication", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static String ctMemphisPersistReplPlan(String url, String token, String name, Object sourceDBEngine, Object targetDBEngine, Object isBiDirectional)
        throws Exception
    {
        JSONObject param = new JSONObject();
        JSONObject replPlan = new JSONObject();
        replPlan.put("name", name);
        replPlan.put("sourceDBEngine", sourceDBEngine);
        replPlan.put("targetDBEngine", targetDBEngine);
        replPlan.put("isBiDirectional", isBiDirectional);
        param.put("replPlan", replPlan);

        JSONObject result = ctMemphis(url, "ctMemphisPersistReplPlan", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return result.get("id").toString();
    }

    private static String ctMemphisPersistSubscription(String url, String token, String name, String description, Object replPlan, Object publication, Object dbEngine, Object database, JSONArray redirectionList)
        throws Exception
    {
        JSONObject param = new JSONObject();
        JSONObject sub = new JSONObject();
        sub.put("name", name);
        sub.put("description", description);
        sub.put("replPlan", replPlan);
        sub.put("publication", publication);
        sub.put("dbEngine", dbEngine);
        sub.put("database", database);
        sub.put("redirectionList", redirectionList);
        param.put("subscription", sub);

        JSONObject result = ctMemphis(url, "ctMemphisPersistSubscription", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return result.get("id").toString();
    }
    
    private static void ctMemphisDeployReplPlan(String url, String token, String id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
        param.put("forceReplace", "true");

        JSONObject result = ctMemphis(url, "ctMemphisDeployReplPlan", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        // wait for deploy to complete
        String actionId = result.get("actionID").toString();
        while (!ctMemphisCheckAction(memphisURL, token, actionId).equals("completed"))
        {
            Thread.sleep(1000);
        }
    }

    private static void ctMemphisResyncFiles(String url, String token, Object id, JSONArray fileList)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
        param.put("fileList", fileList);

        JSONObject result = ctMemphis(url, "ctMemphisResyncFiles", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        // wait for deploy to complete
        Object actionId = result.get("actionID");
        while (!ctMemphisCheckAction(memphisURL, token, actionId).equals("completed"))
        {
            Thread.sleep(1000);
        }
    }

    private static String ctMemphisCheckAction(String url, String token, Object actionId)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("actionID", actionId);
        param.put("checkGroup", "true");

        JSONObject result = ctMemphis(url, "ctMemphisCheckAction", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        JSONObject action = (JSONObject) result.get("action");
        if (action.get("status").toString().equals("error"))
        {
            throw new Exception(action.get("statusMessage").toString());
        }

        return action.get("status").toString();        
    }

    private static void ctMemphisStartReplPlan(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);

        JSONObject result = ctMemphis(url, "ctMemphisStartReplPlan", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static JSONArray ctMemphisGetReplPlans(String url, String token, String name)
        throws Exception
    {
        JSONObject param = new JSONObject();
        if (name != null)
            param.put("name", name);

        JSONObject result = ctMemphis(url, "ctMemphisGetReplPlans", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("replPlanList");
    }

    private static void ctMemphisStopReplPlan(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);

        JSONObject result = ctMemphis(url, "ctMemphisStopReplPlan", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        // wait for stop to complete
        if (result.containsKey("actionID"))
        {
            String actionId = result.get("actionID").toString();
            while (!ctMemphisCheckAction(memphisURL, token, actionId).equals("completed"))
            {
                Thread.sleep(1000);
            }
        }
    }

    private static void ctMemphisRemoveReplPlan(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        JSONObject replPlan = new JSONObject();
        replPlan.put("id", id);
        param.put("replPlan", replPlan);
        param.put("recursive", 1);

        JSONObject result = ctMemphis(url, "ctMemphisRemoveReplPlan", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static String ctMemphisCheckReplPlanStatus(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
        param.put("checkConnection", true);

        JSONObject result = ctMemphis(url, "ctMemphisCheckReplPlanStatus", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        JSONArray statuses = (JSONArray) result.get("replPlanStatusList");
        JSONObject status = (JSONObject) statuses.get(0);
        return status.get("status").toString();        
    }

    private static JSONArray ctMemphisGetPublications(String url, String token, Object dbEngine)
        throws Exception
    {
        JSONObject param = new JSONObject();
        if (dbEngine != null)
            param.put("dbEngine", dbEngine);

        JSONObject result = ctMemphis(url, "ctMemphisGetPublications", token, param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("publicationList");
    }

    private static void ctMemphisRemovePublication(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        JSONObject pub = new JSONObject();
        pub.put("id", id);
        param.put("publication", pub);
        param.put("recursive", 1);

        JSONObject result = ctMemphis(url, "ctMemphisRemovePublication", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static JSONArray ctMemphisGetSubscriptions(String url, String token)
        throws Exception
    {
        JSONObject result = ctMemphis(url, "ctMemphisGetSubscriptions", token, new JSONObject());
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }

        return (JSONArray) result.get("subscriptionList");
    }

    private static void ctMemphisRemoveSubscription(String url, String token, Object id)
        throws Exception
    {
        JSONObject param = new JSONObject();
        param.put("id", id);
    
        JSONObject result = ctMemphis(url, "ctMemphisRemoveSubscription", token,  param);
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static void ctMemphisLogout(String url, String token)
        throws Exception
    {
        JSONObject result = ctMemphis(url, "ctMemphisLogout", token, new JSONObject());
        if (result.get("success").equals("false"))
        {
            JSONObject error = (JSONObject) result.get("error");
            throw new Exception(errorMessage(error));
        }
    }

    private static JSONObject ctMemphis(String server, String function, String token, JSONObject param)
        throws Exception
    {
        if (!server.endsWith("/"))
            server += "/";

        URL url = new URL(server + function);

        if (debug)
            System.err.println(url.toString() + param.toString());

        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type", "application/json");
        conn.setDoOutput(true);
        conn.setDoInput(true);

        if (token != null)
            conn.setRequestProperty("token", token);

        try (DataOutputStream stream = new DataOutputStream(conn.getOutputStream()))
        {
            stream.writeBytes(param.toJSONString());
        }

        InputStreamReader reader = new InputStreamReader(conn.getInputStream(), "UTF-8");
        JSONObject response = (JSONObject) new JSONParser().parse(reader);
        reader.close();

        conn.disconnect();

        return response;
    }
}

