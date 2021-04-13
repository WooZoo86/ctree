import java.io.IOException;
import java.util.List;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

public class Main {

    final static String data[][] = { { "1000", "92867", "CA", "1", "Bryan Williams", "2999 Regency", "Orange" },
            { "1001", "61434", "CT", "1", "Michael Jordan", "13 Main", "Harford" },
            { "1002", "73677", "GA", "1", "Joshua Brown", "4356 Cambridge", "Atlanta" },
            { "1003", "10034", "MO", "1", "Keyon Dooling", "19771 Park Avenue", "Columbia" } };

    public static void main(String[] args) {
        java.util.logging.Logger.getLogger("org.hibernate").setLevel(java.util.logging.Level.OFF);
        System.out.println("This is a demo program to show how you can use Hibernate with c-treeACE.");
        System.out.println("This demo program will use Hibrnate to:");
        System.out.println("1. Delete existing data (if any).");
        System.out.println("2. Insert test data.");
        System.out.println("3. Display test data.");
        System.out.println("Press <ENTER> key to continue...");
        try {
            System.in.read();
        }
        catch (IOException err)
        {}
            
        SessionFactory factory = new Configuration().addClass(Customer.class).buildSessionFactory();

        try (Session session = factory.openSession()) {
            session.beginTransaction();
            if (session.createQuery("from Customer", Customer.class).list().size() > 0) {
                deleteData(session);
            }
            insertData(session);
            displayData(session);
            session.getTransaction().commit();
            session.close();
        }
        System.out.println();
    }

    private static void deleteData(Session session) {
        List<Customer> list = session.createQuery("from Customer", Customer.class).list();
        for (Customer customer : list) {
            session.delete(customer);
        }
    }

    private static void displayData(Session session) {
        // createCriteria(Customer.class).list();
        List<Customer> list = session.createQuery("from Customer", Customer.class).list();
        for (Customer customer : list) {
            System.out.println("\n\t\t" + customer.getNumber() + "   " + customer.getName());
        }
    }

    private static void insertData(Session session) {
        // create on customer entity at a time and persist on the custmast table
        for (int i = 0; i < data.length; i++) {

            Customer customer = new Customer();
            customer.setNumber(data[i][0]);
            customer.setZipCode(data[i][1]);
            customer.setState(data[i][2]);
            customer.setRating(data[i][3]);
            customer.setName(data[i][4]);
            customer.setAddress(data[i][5]);
            customer.setCity(data[i][6]);

            session.save(customer);
        }
    }

}
