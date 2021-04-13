/*
 *      OFFICIAL NOTIFICATION: the following CONFIDENTIAL and PROPRIETARY 
 * 	property legend shall not be removed from this source code module 
 * 	for any reason.
 *
 *	This program is the CONFIDENTIAL and PROPRIETARY property 
 *	of FairCom(R) Corporation. Any unauthorized use, reproduction or
 *	transfer of this computer program is strictly prohibited. The 
 *      contents of this file may not be disclosed to third parties, copied or
 *      duplicated in any form, in whole or in part, without the prior written
 *      permission of the FairCom(R) Corporation.
 *
 *      Copyright (c) 1992 - 2020 FairCom Corporation.
 *	This is an unpublished work, and is subject to limited distribution and
 *	restricted disclosure only. ALL RIGHTS RESERVED.
 *
 *			RESTRICTED RIGHTS LEGEND
 *	Use, duplication, or disclosure by the Government is subject to
 *	restrictions set forth in subparagraph (c)(1)(ii) of the Rights in
 * 	Technical Data and Computer Software clause at DFARS 252.227-7013, and/or
 *      in similar or successor clauses in the FAR, DOD or NASA FAR Supplement.
 *      Unpublished rights reserved under the Copyright Laws of the United States.
 *	FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203.
 *
 *	c-treeACE(tm)	Version 11.5
 */
#ifndef ctIERRH
#define ctIERRH

		/* INTERNAL ERROR CODES */
/*-5*/
/*-6*/
/*-7*/
/*-5000*/
/*-5102*/
/*200*/
/*201*/
/*202*/
/*203*/
/*204*/
/*206*/
/*207*/
/*208*/
/*209*/
/*210*/
/*216*/
/*222*/
/*225*/
/*228*/
/*230*/
/*232*/
/*233*/
/*235*/
/*236*/
/*238*/
/*239*/
/*241*/
/*242*/
/*243*/
/*244*/
/*245*/
/*246*/
/*247*/
/*248*/
/*249*/
/*256*/
/*257*/
/*980*/
/*981*/
/*982*/
/*983*/
/*984*/
/*992*/
/*993*/
/*994*/
/*996*/
/*998*/
/*1101*/
/*1102*/
/*1103*/
/*1105*/
/*1111*/
/*1203*/
/*1964*/
/*1965*/
/*1966*/
/*1967*/
/*2203*/
/*2460*/
/*3333*/
/*6000*/
/*6001*/
/*6002*/
/*6003*/
/*6004*/
/*6005*/
/*6007*/
/*6008*/
/*6009*/
/*6010*/
/*6011*/
/*6012*/
/*6013*/
/*6100*/
/*6101*/

/*7500*/
/*7501*/
/*7502*/
/*7503*/
/*7530*/
/*7531*/
/*7532*/
/*7562*/
/*7632*/
/*7715*/
/*7716*/
/*7717*/
/*7783*/
/*7810*/
/*7987*/
/*8341*/
/*8342*/
/*8484*/
/*8485*/
/*8486*/
/*8487*/
/*8488*/
/*8489*/
/*8494*/
/*8495*/
/*8496*/
/*8497*/
/*8498*/
/*8499*/
/*8501*/
/*8503*/
/*8506*/
/*8512*/
/*8513*/
/*8514*/
/*8520*/
/*8521*/
/*8522*/
/*8601*/
/*8602*/
/*8647*/
/*8648*/
/*8649*/
/*8650*/
/*8651*/
/*8652*/
/*8654*/
/*8655*/
/*8656*/
/*8657*/
/*8658*/
/*8659*/
/*8660*/
/*8661*/
/*8662*/
/*8663*/
/*8665*/
/*8666*/
/*8667*/
/*8668*/
/*8670*/
/*8672*/
/*8673*/
/*8674*/
/*8676*/
/*8677*/
/*8679*/
/*8680*/
/*8681*/
/*8683*/
/*8684*/
/*8685*/
/*8687*/
/*8689*/
/*8690*/
/*8691*/
/*8693*/
/*8695*/
/*8697*/
/*8698*/
/*8699*/
/*8700*/
/*8705*/
/*8706*/
/*8707*/
/*8708*/
/*8709*/
/*8710*/
/*8711*/
/*8715*/
/*8716*/
/*8717*/
/*8718*/
/*8719*/
/*8722*/
/*8723*/
/*8724*/
/*8725*/
/*8726*/
/*8727*/
/*8728*/
/*8729*/
/*8730*/
/*8731*/
/*8732*/
/*8733*/
/*8734*/
/*8735*/
/*8736*/
/*8741*/
/*8742*/
/*8743*/
/*8744*/
/*8745*/
/*8746*/
/*8747*/
/*8748*/
/*8750*/
/*8752*/
/*8753*/
/*8754*/
/*8756*/
/*8761*/
/*8762*/
/*8763*/
/*8764*/
/*8765*/
/*8766*/
/*8767*/
/*8768*/
/*8769*/
/*8771*/
/*8772*/
/*8773*/
/*8774*/
/*8775*/
/*8776*/
/*8777*/
/*8778*/
/*8779*/
/*8780*/
/*8781*/
/*8782*/
/*8783*/
/*8784*/
/*8785*/
/*8788*/
/*8789*/
/*8791*/
/*8792*/
/*8794*/
/*8795*/
/*8796*/
/*8797*/
/*8798*/
/*8799*/
/*8800*/
/*8801*/
/*8870*/
/*8871*/
/*8872*/
/*8873*/
/*8874*/
/*8875*/
/*8876*/
/*8877*/
/*8878*/
/*8879*/
/*8880*/
/*8881*/
/*8882*/
/*8883*/
/*8884*/
/*8885*/
/*8886*/
/*8887*/
/*8888*/
/*8889*/
/*8890*/
/*8891*/
/*8892*/
/*8893*/
/*8894*/
/*8895*/
/*8896*/
/*8897*/
/*8898*/
/*8899*/
/*8900*/
/*8901*/
/*8902*/
/*8903*/
/*8904*/
/*8905*/
/*8906*/
/*8907*/
/*8909*/
/*8911*/
/*8914*/
/*8915*/
/*8916*/
/*8917*/
/*8918*/
/*8919*/
/*8920*/
/*8921*/
/*8922*/
/*8923*/
/*8924*/
/*8925*/
/*8926*/
/*8928*/
/*8929*/
/*8930*/
/*8931*/
/*8932*/
/*8933*/
/*8934*/
/*8935*/
/*8936*/
/*8937*/
/*8938*/
/*8939*/
/*8940*/
/*8944*/
/*8945*/
/*8946*/
/*8948*/
/*8949*/
/*8950*/
/*8952*/
/*8953*/
/*8954*/
/*8960*/
/*8961*/
/*8962*/
/*8965*/
/*8966*/
/*8967*/
/*8968*/
/*8969*/
/*8970*/
/*8971*/
/*8972*/
/*8973*/
/*8975*/
/*8978*/
/*8979*/
/*8980*/
/*8981*/
/*8982*/
/*8983*/
/*8986*/
/*8987*/
/*8988*/
/*8989*/
/*8990*/
/*8991*/
/*8992*/
/*8993*/
/*8994*/
/*8995*/
/*9003*/
/*9010*/
/*9011*/
/*9012*/
/*9013*/
/*9042*/
/*9061*/
/*9070*/
/*9074*/
/*9090*/
/*9223*/
/*9450*/
/*9452*/
/*9453*/
/*9454*/
/*9455*/
/*9475*/
/*9476*/
/*9477*/
/*9495*/
/*9773*/
/*9775*/
/*9800*/
/*9875*/
/*9959*/
/*9960*/
/*9961*/
/*9962*/
/*9965*/
/*9966*/
/*9967*/
/*9968*/
/*9970*/
/*9976*/
/*9978*/
/*9979*/
/*9992*/
/*9996*/
/*9997*/
/*10010*/
/*10011*/
#define	INT_MEM7000_ERR	7000	/* Internal Error, report to Faircom. */
#define	INT_MEM7001_ERR	7001	/* Internal Error, report to Faircom. */
#define	INT_MEM7002_ERR	7002	/* Internal Error, report to Faircom. */
#define	INT_MEM7003_ERR	7003	/* Internal Error, report to Faircom. */
#define	INT_MEM7004_ERR	7004	/* Internal Error, report to Faircom. */
#define	INT_MEM7005_ERR	7005	/* Internal Error, report to Faircom. */
#define	INT_MEM7006_ERR	7006	/* Internal Error, report to Faircom. */
#define	INT_MEM7007_ERR	7007	/* Internal Error, report to Faircom. */
#define	INT_MEM7008_ERR	7008	/* Internal Error, report to Faircom. */
#define	INT_MEM7009_ERR	7009	/* Internal Error, report to Faircom. */
#define	INT_MEM7010_ERR	7010	/* Internal Error, report to Faircom. */
#define	INT_MEM7011_ERR	7011	/* Internal Error, report to Faircom. */
#define	INT_MEM7012_ERR	7012	/* Internal Error, report to Faircom. */
#define	INT_MEM7013_ERR	7013	/* Internal Error, report to Faircom. */
#define	INT_MEM7014_ERR	7014	/* Internal Error, report to Faircom. */
#define	INT_MEM7015_ERR	7015	/* Internal Error, report to Faircom. */
#define	INT_MEM7016_ERR	7016	/* Internal Error, report to Faircom. */
#define	INT_MEM7017_ERR	7017	/* Internal Error, report to Faircom. */
#define	INT_MEM7018_ERR	7018	/* Internal Error, report to Faircom. */
#define	INT_MEM7019_ERR	7019	/* Internal Error, report to Faircom. */
#define	INT_MEM7020_ERR	7020	/* Internal Error, report to Faircom. */
#define	INT_MEM7021_ERR	7021	/* Internal Error, report to Faircom. */
#define	INT_MEM7022_ERR	7022	/* Internal Error, report to Faircom. */
#define	INT_MEM7023_ERR	7023	/* Internal Error, report to Faircom. */
#define	INT_MEM7024_ERR	7024	/* Internal Error, report to Faircom. */
#define	INT_MEM7025_ERR	7025	/* Internal Error, report to Faircom. */
#define	INT_MEM7026_ERR	7026	/* Internal Error, report to Faircom. */
#define	INT_MEM7027_ERR	7027	/* Internal Error, report to Faircom. */
#define	INT_MEM7028_ERR	7028	/* Internal Error, report to Faircom. */
#define	INT_MEM7029_ERR	7029	/* Internal Error, report to Faircom. */
#define	INT_MEM7030_ERR	7030	/* Internal Error, report to Faircom. */
#define	INT_MEM7031_ERR	7031	/* Internal Error, report to Faircom. */
#define	INT_MEM7032_ERR	7032	/* Internal Error, report to Faircom. */
#define	INT_MEM7033_ERR	7033	/* Internal Error, report to Faircom. */
#define	INT_MEM7034_ERR	7034	/* Internal Error, report to Faircom. */
#define	INT_MEM7035_ERR	7035	/* Internal Error, report to Faircom. */
#define	INT_MEM7036_ERR	7036	/* Internal Error, report to Faircom. */
#define	INT_MEM7037_ERR	7037	/* Internal Error, report to Faircom. */
#define	INT_MEM7038_ERR	7038	/* Internal Error, report to Faircom. */
#define	INT_MEM7039_ERR	7039	/* Internal Error, report to Faircom. */
#define	INT_MEM7040_ERR	7040	/* Internal Error, report to Faircom. */
#define	INT_MEM7041_ERR	7041	/* Internal Error, report to Faircom. */
#define	INT_MEM7042_ERR	7042	/* Internal Error, report to Faircom. */
#define	INT_MEM7043_ERR	7043	/* Internal Error, report to Faircom. */
#define	INT_MEM7044_ERR	7044	/* Internal Error, report to Faircom. */
#define	INT_MEM7045_ERR	7045	/* Internal Error, report to Faircom. */
#define	INT_MEM7046_ERR	7046	/* Internal Error, report to Faircom. */
#define	INT_MEM7047_ERR	7047	/* Internal Error, report to Faircom. */
#define	INT_MEM7048_ERR	7048	/* Internal Error, report to Faircom. */
#define	INT_MEM7049_ERR	7049	/* Internal Error, report to Faircom. */
#define	INT_MEM7050_ERR	7050	/* Internal Error, report to Faircom. */
#define	INT_MEM7051_ERR	7051	/* Internal Error, report to Faircom. */
#define	INT_MEM7052_ERR	7052	/* Internal Error, report to Faircom. */
#define	INT_MEM7053_ERR	7053	/* Internal Error, report to Faircom. */
#define	INT_MEM7054_ERR	7054	/* Internal Error, report to Faircom. */
#define	INT_MEM7055_ERR	7055	/* Internal Error, report to Faircom. */
#define	INT_MEM7056_ERR	7056	/* Internal Error, report to Faircom. */
#define	INT_MEM7057_ERR	7057	/* Internal Error, report to Faircom. */
#define	INT_MEM7058_ERR	7058	/* Internal Error, report to Faircom. */
#define	INT_MEM7059_ERR	7059	/* Internal Error, report to Faircom. */
#define	INT_MEM7060_ERR	7060	/* Internal Error, report to Faircom. */
#define	INT_MEM7061_ERR	7061	/* Internal Error, report to Faircom. */
#define	INT_MEM7062_ERR	7062	/* Internal Error, report to Faircom. */
#define	INT_MEM7063_ERR	7063	/* Internal Error, report to Faircom. */
#define	INT_MEM7064_ERR	7064	/* Internal Error, report to Faircom. */
#define	INT_MEM7065_ERR	7065	/* Internal Error, report to Faircom. */
#define	INT_MEM7066_ERR	7066	/* Internal Error, report to Faircom. */
#define	INT_MEM7067_ERR	7067	/* Internal Error, report to Faircom. */
#define	INT_MEM7068_ERR	7068	/* Internal Error, report to Faircom. */
#define	INT_MEM7069_ERR	7069	/* Internal Error, report to Faircom. */
#define	INT_MEM7070_ERR	7070	/* Internal Error, report to Faircom. */
#define	INT_MEM7071_ERR	7071	/* Internal Error, report to Faircom. */
#define	INT_MEM7072_ERR	7072	/* Internal Error, report to Faircom. */
#define	INT_MEM7073_ERR	7073	/* Internal Error, report to Faircom. */
#define	INT_MEM7074_ERR	7074	/* Internal Error, report to Faircom. */
#define	INT_MEM7075_ERR	7075	/* Internal Error, report to Faircom. */
#define	INT_MEM7076_ERR	7076	/* Internal Error, report to Faircom. */
#define	INT_MEM7077_ERR	7077	/* Internal Error, report to Faircom. */
#define	INT_MEM7078_ERR	7078	/* Internal Error, report to Faircom. */
#define	INT_MEM7079_ERR	7079	/* Internal Error, report to Faircom. */
#define	INT_MEM7080_ERR	7080	/* Internal Error, report to Faircom. */
#define	INT_MEM7081_ERR	7081	/* Internal Error, report to Faircom. */
#define	INT_MEM7082_ERR	7082	/* Internal Error, report to Faircom. */
#define	INT_MEM7083_ERR	7083	/* Internal Error, report to Faircom. */
#define	INT_MEM7084_ERR	7084	/* Internal Error, report to Faircom. */
#define	INT_MEM7085_ERR	7085	/* Internal Error, report to Faircom. */
#define	INT_MEM7086_ERR	7086	/* Internal Error, report to Faircom. */
#define	INT_MEM7087_ERR	7087	/* Internal Error, report to Faircom. */
#define	INT_MEM7088_ERR	7088	/* Internal Error, report to Faircom. */
#define	INT_MEM7089_ERR	7089	/* Internal Error, report to Faircom. */
#define	INT_MEM7090_ERR	7090	/* Internal Error, report to Faircom. */
#define	INT_MEM7091_ERR	7091	/* Internal Error, report to Faircom. */
#define	INT_MEM7092_ERR	7092	/* Internal Error, report to Faircom. */
#define	INT_MEM7093_ERR	7093	/* Internal Error, report to Faircom. */
#define	INT_MEM7094_ERR	7094	/* Internal Error, report to Faircom. */
#define	INT_MEM7095_ERR	7095	/* Internal Error, report to Faircom. */
#define	INT_MEM7096_ERR	7096	/* Internal Error, report to Faircom. */
#define	INT_MEM7097_ERR	7097	/* Internal Error, report to Faircom. */
#define	INT_MEM7098_ERR	7098	/* Internal Error, report to Faircom. */
#define	INT_MEM7099_ERR	7099	/* Internal Error, report to Faircom. */
#define	INT_MEM7100_ERR	7100	/* Internal Error, report to Faircom. */
#define	INT_MEM7101_ERR	7101	/* Internal Error, report to Faircom. */
#define	INT_MEM7102_ERR	7102	/* Internal Error, report to Faircom. */
#define	INT_MEM7103_ERR	7103	/* Internal Error, report to Faircom. */
#define	INT_MEM7104_ERR	7104	/* Internal Error, report to Faircom. */
#define	INT_MEM7105_ERR	7105	/* Internal Error, report to Faircom. */
#define	INT_MEM7106_ERR	7106	/* Internal Error, report to Faircom. */
#define	INT_MEM7107_ERR	7107	/* Internal Error, report to Faircom. */
#define	INT_MEM7108_ERR	7108	/* Internal Error, report to Faircom. */
#define	INT_MEM7109_ERR	7109	/* Internal Error, report to Faircom. */
#define	INT_MEM7110_ERR	7110	/* Internal Error, report to Faircom. */
#define	INT_MEM7111_ERR	7111	/* Internal Error, report to Faircom. */
#define	INT_MEM7112_ERR	7112	/* Internal Error, report to Faircom. */
#define	INT_MEM7113_ERR	7113	/* Internal Error, report to Faircom. */
#define	INT_MEM7114_ERR	7114	/* Internal Error, report to Faircom. */
#define	INT_MEM7115_ERR	7115	/* Internal Error, report to Faircom. */
#define	INT_MEM7116_ERR	7116	/* Internal Error, report to Faircom. */
#define	INT_MEM7117_ERR	7117	/* Internal Error, report to Faircom. */
#define	INT_MEM7118_ERR	7118	/* Internal Error, report to Faircom. */
#define	INT_MEM7119_ERR	7119	/* Internal Error, report to Faircom. */
#define	INT_MEM7120_ERR	7120	/* Internal Error, report to Faircom. */
#define	INT_MEM7121_ERR	7121	/* Internal Error, report to Faircom. */
#define	INT_MEM7122_ERR	7122	/* Internal Error, report to Faircom. */
#define	INT_MEM7123_ERR	7123	/* Internal Error, report to Faircom. */
#define	INT_MEM7124_ERR	7124	/* Internal Error, report to Faircom. */
#define	INT_MEM7125_ERR	7125	/* Internal Error, report to Faircom. */
#define	INT_MEM7126_ERR	7126	/* Internal Error, report to Faircom. */
#define	INT_MEM7127_ERR	7127	/* Internal Error, report to Faircom. */
#define	INT_MEM7128_ERR	7128	/* Internal Error, report to Faircom. */
#define	INT_MEM7129_ERR	7129	/* Internal Error, report to Faircom. */
#define	INT_MEM7130_ERR	7130	/* Internal Error, report to Faircom. */
#define	INT_MEM7131_ERR	7131	/* Internal Error, report to Faircom. */
#define	INT_MEM7132_ERR	7132	/* Internal Error, report to Faircom. */
#define	INT_MEM7133_ERR	7133	/* Internal Error, report to Faircom. */
#define	INT_MEM7134_ERR	7134	/* Internal Error, report to Faircom. */
#define	INT_MEM7135_ERR	7135	/* Internal Error, report to Faircom. */
#define	INT_MEM7136_ERR	7136	/* Internal Error, report to Faircom. */
#define	INT_MEM7137_ERR	7137	/* Internal Error, report to Faircom. */
#define	INT_MEM7138_ERR	7138	/* Internal Error, report to Faircom. */
#define	INT_MEM7139_ERR	7139	/* Internal Error, report to Faircom. */
#define	INT_MEM7140_ERR	7140	/* Internal Error, report to Faircom. */
#define	INT_MEM7141_ERR	7141	/* Internal Error, report to Faircom. */
#define	INT_MEM7142_ERR	7142	/* Internal Error, report to Faircom. */
#define	INT_MEM7143_ERR	7143	/* Internal Error, report to Faircom. */
#define	INT_MEM7144_ERR	7144	/* Internal Error, report to Faircom. */
#define	INT_MEM7145_ERR	7145	/* Internal Error, report to Faircom. */
#define	INT_MEM7146_ERR	7146	/* Internal Error, report to Faircom. */
#define	INT_MEM7147_ERR	7147	/* Internal Error, report to Faircom. */
#define	INT_MEM7148_ERR	7148	/* Internal Error, report to Faircom. */
#define	INT_MEM7149_ERR	7149	/* Internal Error, report to Faircom. */
#define	INT_MEM7150_ERR	7150	/* Internal Error, report to Faircom. */
#define	INT_MEM7151_ERR	7151	/* Internal Error, report to Faircom. */
#define	INT_MEM7152_ERR	7152	/* Internal Error, report to Faircom. */
#define	INT_MEM7153_ERR	7153	/* Internal Error, report to Faircom. */
#define	INT_MEM7154_ERR	7154	/* Internal Error, report to Faircom. */
#define	INT_MEM7155_ERR	7155	/* Internal Error, report to Faircom. */
#define	INT_MEM7156_ERR	7156	/* Internal Error, report to Faircom. */
#define	INT_MEM7157_ERR	7157	/* Internal Error, report to Faircom. */
#define	INT_MEM7158_ERR	7158	/* Internal Error, report to Faircom. */
#define	INT_MEM7159_ERR	7159	/* Internal Error, report to Faircom. */
#define	INT_MEM7160_ERR	7160	/* Internal Error, report to Faircom. */
#define	INT_MEM7161_ERR	7161	/* Internal Error, report to Faircom. */
#define	INT_MEM7162_ERR	7162	/* Internal Error, report to Faircom. */
#define	INT_MEM7163_ERR	7163	/* Internal Error, report to Faircom. */
#define	INT_MEM7164_ERR	7164	/* Internal Error, report to Faircom. */
#define	INT_MEM7165_ERR	7165	/* Internal Error, report to Faircom. */
#define	INT_MEM7166_ERR	7166	/* Internal Error, report to Faircom. */
#define	INT_MEM7167_ERR	7167	/* Internal Error, report to Faircom. */
#define	INT_MEM7168_ERR	7168	/* Internal Error, report to Faircom. */
#define	INT_MEM7171_ERR	7171	/* Internal Error, report to Faircom. */
#define	INT_MEM7172_ERR	7172	/* Internal Error, report to Faircom. */
#define	INT_MEM7173_ERR	7173	/* Internal Error, report to Faircom. */
#define	INT_MEM7174_ERR	7174	/* Internal Error, report to Faircom. */
#define	INT_MEM7175_ERR	7175	/* Internal Error, report to Faircom. */
#define	INT_MEM7176_ERR	7176	/* Internal Error, report to Faircom. */
#define	INT_MEM7177_ERR	7177	/* Internal Error, report to Faircom. */
#define	INT_MEM7178_ERR	7178	/* Internal Error, report to Faircom. */
#define	INT_MEM7179_ERR	7179	/* Internal Error, report to Faircom. */
#define	INT_MEM7180_ERR	7180	/* Internal Error, report to Faircom. */
#define	INT_MEM7181_ERR	7181	/* Internal Error, report to Faircom. */
#define	INT_MEM7182_ERR	7182	/* Internal Error, report to Faircom. */
#define	INT_MEM7183_ERR	7183	/* Internal Error, report to Faircom. */
#define	INT_MEM7184_ERR	7184	/* Internal Error, report to Faircom. */
#define	INT_MEM7185_ERR	7185	/* Internal Error, report to Faircom. */
#define	INT_MEM7186_ERR	7186	/* Internal Error, report to Faircom. */
#define	INT_MEM7187_ERR	7187	/* Internal Error, report to Faircom. */
#define	INT_MEM7188_ERR	7188	/* Internal Error, report to Faircom. */
#define	INT_MEM7189_ERR	7189	/* Internal Error, report to Faircom. */
#define	INT_MEM7190_ERR	7190	/* Internal Error, report to Faircom. */
#define	INT_MEM7191_ERR	7191	/* Internal Error, report to Faircom. */
#define	INT_MEM7192_ERR	7192	/* Internal Error, report to Faircom. */
#define	INT_MEM7193_ERR	7193	/* Internal Error, report to Faircom. */
#define	INT_MEM7194_ERR	7194	/* Internal Error, report to Faircom. */
#define	INT_MEM7195_ERR	7195	/* Internal Error, report to Faircom. */
#define	INT_MEM7196_ERR	7196	/* Internal Error, report to Faircom. */
#define	INT_MEM7197_ERR	7197	/* Internal Error, report to Faircom. */
#define	INT_MEM7198_ERR	7198	/* Internal Error, report to Faircom. */
#define	INT_MEM7199_ERR	7199	/* Internal Error, report to Faircom. */
#define	INT_MEM7200_ERR	7200	/* Internal Error, report to Faircom. */
#define	INT_MEM7201_ERR	7201	/* Internal Error, report to Faircom. */
#define	INT_MEM7202_ERR	7202	/* Internal Error, report to Faircom. */
#define	INT_MEM7203_ERR	7203	/* Internal Error, report to Faircom. */
#define	INT_MEM7204_ERR	7204	/* Internal Error, report to Faircom. */
#define	INT_MEM7205_ERR	7205	/* Internal Error, report to Faircom. */
#define	INT_MEM7206_ERR	7206	/* Internal Error, report to Faircom. */
#define	INT_MEM7207_ERR	7207	/* Internal Error, report to Faircom. */
#define	INT_MEM7208_ERR	7208	/* Internal Error, report to Faircom. */
#define	INT_MEM7209_ERR	7209	/* Internal Error, report to Faircom. */
#define	INT_MEM7210_ERR	7210	/* Internal Error, report to Faircom. */
#define	INT_MEM7211_ERR	7211	/* Internal Error, report to Faircom. */
#define	INT_MEM7212_ERR	7212	/* Internal Error, report to Faircom. */
#define	INT_MEM7213_ERR	7213	/* Internal Error, report to Faircom. */
#define	INT_MEM7214_ERR	7214	/* Internal Error, report to Faircom. */
#define	INT_MEM7215_ERR	7215	/* Internal Error, report to Faircom. */
#define	INT_MEM7216_ERR	7216	/* Internal Error, report to Faircom. */
#define	INT_MEM7217_ERR	7217	/* Internal Error, report to Faircom. */
#define	INT_MEM7218_ERR	7218	/* Internal Error, report to Faircom. */
#define	INT_MEM7219_ERR	7219	/* Internal Error, report to Faircom. */
#define	INT_MEM7220_ERR	7220	/* Internal Error, report to Faircom. */
#define	INT_MEM7221_ERR	7221	/* Internal Error, report to Faircom. */
#define	INT_MEM7222_ERR	7222	/* Internal Error, report to Faircom. */
#define	INT_MEM7223_ERR	7223	/* Internal Error, report to Faircom. */
#define	INT_MEM7224_ERR	7224	/* Internal Error, report to Faircom. */
#define	INT_MEM7225_ERR	7225	/* Internal Error, report to Faircom. */
#define	INT_MEM7226_ERR	7226	/* Internal Error, report to Faircom. */
#define	INT_MEM7227_ERR	7227	/* Internal Error, report to Faircom. */
#define	INT_MEM7228_ERR	7228	/* Internal Error, report to Faircom. */
#define	INT_MEM7229_ERR	7229	/* Internal Error, report to Faircom. */
#define	INT_MEM7230_ERR	7230	/* Internal Error, report to Faircom. */
#define	INT_MEM7231_ERR	7231	/* Internal Error, report to Faircom. */
#define	INT_MEM7232_ERR	7232	/* Internal Error, report to Faircom. */
#define	INT_MEM7233_ERR	7233	/* Internal Error, report to Faircom. */
#define	INT_MEM7234_ERR	7234	/* Internal Error, report to Faircom. */
#define	INT_MEM7235_ERR	7235	/* Internal Error, report to Faircom. */
#define	INT_MEM7236_ERR	7236	/* Internal Error, report to Faircom. */
#define	INT_MEM7237_ERR	7237	/* Internal Error, report to Faircom. */
#define	INT_MEM7238_ERR	7238	/* Internal Error, report to Faircom. */
#define	INT_MEM7239_ERR	7239	/* Internal Error, report to Faircom. */
#define	INT_MEM7240_ERR	7240	/* Internal Error, report to Faircom. */
#define	INT_MEM7241_ERR	7241	/* Internal Error, report to Faircom. */
#define	INT_MEM7242_ERR	7242	/* Internal Error, report to Faircom. */
#define	INT_MEM7243_ERR	7243	/* Internal Error, report to Faircom. */
#define	INT_MEM7244_ERR	7244	/* Internal Error, report to Faircom. */
#define	INT_MEM7245_ERR	7245	/* Internal Error, report to Faircom. */
#define	INT_MEM7246_ERR	7246	/* Internal Error, report to Faircom. */
#define	INT_MEM7247_ERR	7247	/* Internal Error, report to Faircom. */
#define	INT_MEM7248_ERR	7248	/* Internal Error, report to Faircom. */
#define	INT_MEM7249_ERR	7249	/* Internal Error, report to Faircom. */
#define	INT_MEM7250_ERR	7250	/* Internal Error, report to Faircom. */
#define	INT_MEM7251_ERR	7251	/* Internal Error, report to Faircom. */
#define	INT_MEM7252_ERR	7252	/* Internal Error, report to Faircom. */
#define	INT_MEM7253_ERR	7253	/* Internal Error, report to Faircom. */
#define	INT_MEM7254_ERR	7254	/* Internal Error, report to Faircom. */
#define	INT_MEM7255_ERR	7255	/* Internal Error, report to Faircom. */
#define	INT_MEM7256_ERR	7256	/* Internal Error, report to Faircom. */
#define	INT_MEM7257_ERR	7257	/* Internal Error, report to Faircom. */
#define	INT_MEM7258_ERR	7258	/* Internal Error, report to Faircom. */
#define	INT_MEM7259_ERR	7259	/* Internal Error, report to Faircom. */
#define	INT_MEM7260_ERR	7260	/* Internal Error, report to Faircom. */
#define	INT_MEM7261_ERR	7261	/* Internal Error, report to Faircom. */
#define	INT_MEM7262_ERR	7262	/* Internal Error, report to Faircom. */
#define	INT_MEM7268_ERR	7268	/* Internal Error, report to Faircom. */
#define	INT_MEM7269_ERR	7269	/* Internal Error, report to Faircom. */
#define	INT_MEM7270_ERR	7270	/* Internal Error, report to Faircom. */
#define	INT_MEM7271_ERR	7271	/* Internal Error, report to Faircom. */
#define	INT_MEM7272_ERR	7272	/* Internal Error, report to Faircom. */
#define	INT_MEM7273_ERR	7273	/* Internal Error, report to Faircom. */
#define	INT_MEM7274_ERR	7274	/* Internal Error, report to Faircom. */
#define	INT_MEM7275_ERR	7275	/* Internal Error, report to Faircom. */
#define	INT_MEM7276_ERR	7276	/* Internal Error, report to Faircom. */
#define	INT_MEM7277_ERR	7277	/* Internal Error, report to Faircom. */
#define	INT_MEM7278_ERR	7278	/* Internal Error, report to Faircom. */
#define	INT_MEM7279_ERR	7279	/* Internal Error, report to Faircom. */
#define	INT_MEM7280_ERR	7280	/* Internal Error, report to Faircom. */
#define	INT_MEM7281_ERR	7281	/* Internal Error, report to Faircom. */
#define	INT_MEM7282_ERR	7282	/* Internal Error, report to Faircom. */
#define	INT_MEM7283_ERR	7283	/* Internal Error, report to Faircom. */
#define	INT_MEM7284_ERR	7284	/* Internal Error, report to Faircom. */
#define	INT_MEM7285_ERR	7285	/* Internal Error, report to Faircom. */
#define	INT_MEM7286_ERR	7286	/* Internal Error, report to Faircom. */
#define	INT_MEM7287_ERR	7287	/* Internal Error, report to Faircom. */
#define	INT_MEM7288_ERR	7288	/* Internal Error, report to Faircom. */
#define	INT_MEM7289_ERR	7289	/* Internal Error, report to Faircom. */
#define	INT_MEM7290_ERR	7290	/* Internal Error, report to Faircom. */
#define	INT_MEM7291_ERR	7291	/* Internal Error, report to Faircom. */
#define	INT_MEM7292_ERR	7292	/* Internal Error, report to Faircom. */
#define	INT_MEM7293_ERR	7293	/* Internal Error, report to Faircom. */
#define	INT_MEM7294_ERR	7294	/* Internal Error, report to Faircom. */
#define	INT_MEM7295_ERR	7295	/* Internal Error, report to Faircom. */
#define	INT_MEM7296_ERR	7296	/* Internal Error, report to Faircom. */
#define	INT_MEM7297_ERR	7297	/* Internal Error, report to Faircom. */
#define	INT_MEM7298_ERR	7298	/* Internal Error, report to Faircom. */
#define	INT_MEM7299_ERR	7299	/* Internal Error, report to Faircom. */
#define	INT_MEM7300_ERR	7300	/* Internal Error, report to Faircom. */
#define	INT_MEM7301_ERR	7301	/* Internal Error, report to Faircom. */
#define	INT_MEM7302_ERR	7302	/* Internal Error, report to Faircom. */
#define	INT_MEM7303_ERR	7303	/* Internal Error, report to Faircom. */
#define	INT_MEM7304_ERR	7304	/* Internal Error, report to Faircom. */
#define	INT_MEM7305_ERR	7305	/* Internal Error, report to Faircom. */
#define	INT_MEM7306_ERR	7306	/* Internal Error, report to Faircom. */
#define	INT_MEM7307_ERR	7307	/* Internal Error, report to Faircom. */
#define	INT_MEM7308_ERR	7308	/* Internal Error, report to Faircom. */
#define	INT_MEM7309_ERR	7309	/* Internal Error, report to Faircom. */
#define	INT_MEM7310_ERR	7310	/* Internal Error, report to Faircom. */
#define	INT_MEM7311_ERR	7311	/* Internal Error, report to Faircom. */
#define	INT_MEM7312_ERR	7312	/* Internal Error, report to Faircom. */
#define	INT_MEM7313_ERR	7313	/* Internal Error, report to Faircom. */
#define	INT_MEM7314_ERR	7314	/* Internal Error, report to Faircom. */
#define	INT_MEM7315_ERR	7315	/* Internal Error, report to Faircom. */
#define	INT_MEM7316_ERR	7316	/* Internal Error, report to Faircom. */
#define	INT_MEM7317_ERR	7317	/* Internal Error, report to Faircom. */
#define	INT_MEM7318_ERR	7318	/* Internal Error, report to Faircom. */
#define	INT_MEM7319_ERR	7319	/* Internal Error, report to Faircom. */
#define	INT_MEM7320_ERR	7320	/* Internal Error, report to Faircom. */
#define	INT_MEM7321_ERR	7321	/* Internal Error, report to Faircom. */
#define	INT_MEM7322_ERR	7322	/* Internal Error, report to Faircom. */
#define	INT_MEM7323_ERR	7323	/* Internal Error, report to Faircom. */
#define	INT_MEM7324_ERR	7324	/* Internal Error, report to Faircom. */
#define	INT_MEM7325_ERR	7325	/* Internal Error, report to Faircom. */
#define	INT_MEM7326_ERR	7326	/* Internal Error, report to Faircom. */
#define	INT_MEM7327_ERR	7327	/* Internal Error, report to Faircom. */
#define	INT_MEM7328_ERR	7328	/* Internal Error, report to Faircom. */
#define	INT_MEM7329_ERR	7329	/* Internal Error, report to Faircom. */
#define	INT_MEM7330_ERR	7330	/* Internal Error, report to Faircom. */
#define	INT_MEM7331_ERR	7331	/* Internal Error, report to Faircom. */
#define	INT_MEM7332_ERR	7332	/* Internal Error, report to Faircom. */
#define	INT_MEM7333_ERR	7333	/* Internal Error, report to Faircom. */
#define	INT_MEM7334_ERR	7334	/* Internal Error, report to Faircom. */
#define	INT_MEM7335_ERR	7335	/* Internal Error, report to Faircom. */
#define	INT_MEM7336_ERR	7336	/* Internal Error, report to Faircom. */
#define	INT_MEM7337_ERR	7337	/* Internal Error, report to Faircom. */
#define	INT_MEM7338_ERR	7338	/* Internal Error, report to Faircom. */
#define	INT_MEM7339_ERR	7339	/* Internal Error, report to Faircom. */
#define	INT_MEM7340_ERR	7340	/* Internal Error, report to Faircom. */
#define	INT_MEM7341_ERR	7341	/* Internal Error, report to Faircom. */
#define	INT_MEM7342_ERR	7342	/* Internal Error, report to Faircom. */
#define	INT_MEM7343_ERR	7343	/* Internal Error, report to Faircom. */
#define	INT_MEM7344_ERR	7344	/* Internal Error, report to Faircom. */
#define	INT_MEM7345_ERR	7345	/* Internal Error, report to Faircom. */
#define	INT_MEM7346_ERR	7346	/* Internal Error, report to Faircom. */
#define	INT_MEM7347_ERR	7347	/* Internal Error, report to Faircom. */
#define	INT_MEM7348_ERR	7348	/* Internal Error, report to Faircom. */
#define	INT_MEM7349_ERR	7349	/* Internal Error, report to Faircom. */
#define	INT_MEM7350_ERR	7350	/* Internal Error, report to Faircom. */
#define	INT_MEM7351_ERR	7351	/* Internal Error, report to Faircom. */
#define	INT_MEM7352_ERR	7352	/* Internal Error, report to Faircom. */
#define	INT_MEM7353_ERR	7353	/* Internal Error, report to Faircom. */
#define	INT_MEM7354_ERR	7354	/* Internal Error, report to Faircom. */
#define	INT_MEM7355_ERR	7355	/* Internal Error, report to Faircom. */
#define	INT_MEM7356_ERR	7356	/* Internal Error, report to Faircom. */
#define	INT_MEM7357_ERR	7357	/* Internal Error, report to Faircom. */
#define	INT_MEM7358_ERR	7358	/* Internal Error, report to Faircom. */
#define	INT_MEM7359_ERR	7359	/* Internal Error, report to Faircom. */
#define	INT_MEM7360_ERR	7360	/* Internal Error, report to Faircom. */
#define	INT_MEM7361_ERR	7361	/* Internal Error, report to Faircom. */
#define	INT_MEM7362_ERR	7362	/* Internal Error, report to Faircom. */
#define	INT_MEM7363_ERR	7363	/* Internal Error, report to Faircom. */
#define	INT_MEM7364_ERR	7364	/* Internal Error, report to Faircom. */
#define	INT_MEM7365_ERR	7365	/* Internal Error, report to Faircom. */
#define	INT_MEM7366_ERR	7366	/* Internal Error, report to Faircom. */
#define	INT_MEM7367_ERR	7367	/* Internal Error, report to Faircom. */
#define	INT_MEM7368_ERR	7368	/* Internal Error, report to Faircom. */
#define	INT_MEM7369_ERR	7369	/* Internal Error, report to Faircom. */
#define	INT_MEM7370_ERR	7370	/* Internal Error, report to Faircom. */
#define	INT_MEM7371_ERR	7371	/* Internal Error, report to Faircom. */
#define	INT_MEM7372_ERR	7372	/* Internal Error, report to Faircom. */
#define	INT_MEM7373_ERR	7373	/* Internal Error, report to Faircom. */
#define	INT_MEM7374_ERR	7374	/* Internal Error, report to Faircom. */
#define	INT_MEM7375_ERR	7375	/* Internal Error, report to Faircom. */
#define	INT_MEM7376_ERR	7376	/* Internal Error, report to Faircom. */
#define	INT_MEM7377_ERR	7377	/* Internal Error, report to Faircom. */
#define	INT_MEM7378_ERR	7378	/* Internal Error, report to Faircom. */
#define	INT_MEM7379_ERR	7379	/* Internal Error, report to Faircom. */
#define	INT_MEM7380_ERR	7380	/* Internal Error, report to Faircom. */
#define	INT_MEM7381_ERR	7381	/* Internal Error, report to Faircom. */
#define	INT_MEM7382_ERR	7382	/* Internal Error, report to Faircom. */
#define	INT_MEM7383_ERR	7383	/* Internal Error, report to Faircom. */
#define	INT_MEM7384_ERR	7384	/* Internal Error, report to Faircom. */
#define	INT_MEM7385_ERR	7385	/* Internal Error, report to Faircom. */
#define	INT_MEM7386_ERR	7386	/* Internal Error, report to Faircom. */
#define	INT_MEM7387_ERR	7387	/* Internal Error, report to Faircom. */
#define	INT_MEM7388_ERR	7388	/* Internal Error, report to Faircom. */
#define	INT_MEM7389_ERR	7389	/* Internal Error, report to Faircom. */
#define	INT_MEM7390_ERR	7390	/* Internal Error, report to Faircom. */
#define	INT_MEM7391_ERR	7391	/* Internal Error, report to Faircom. */
#define	INT_MEM7392_ERR	7392	/* Internal Error, report to Faircom. */
#define	INT_MEM7393_ERR	7393	/* Internal Error, report to Faircom. */
#define	INT_MEM7394_ERR	7394	/* Internal Error, report to Faircom. */
#define	INT_MEM7395_ERR	7395	/* Internal Error, report to Faircom. */
#define	INT_MEM7396_ERR	7396	/* Internal Error, report to Faircom. */
#define	INT_MEM7397_ERR	7397	/* Internal Error, report to Faircom. */
#define	INT_MEM7398_ERR	7398	/* Internal Error, report to Faircom. */
#define	INT_MEM7399_ERR	7399	/* Internal Error, report to Faircom. */
#define	INT_MEM7400_ERR	7400	/* Internal Error, report to Faircom. */
#define	INT_MEM7401_ERR	7401	/* Internal Error, report to Faircom. */
#define	INT_MEM7402_ERR	7402	/* Internal Error, report to Faircom. */
#define	INT_MEM7403_ERR	7403	/* Internal Error, report to Faircom. */
#define	INT_MEM7404_ERR	7404	/* Internal Error, report to Faircom. */
#define	INT_MEM7405_ERR	7405	/* Internal Error, report to Faircom. */
#define	INT_MEM7406_ERR	7406	/* Internal Error, report to Faircom. */
#define	INT_MEM7407_ERR	7407	/* Internal Error, report to Faircom. */
#define	INT_MEM7408_ERR	7408	/* Internal Error, report to Faircom. */
#define	INT_MEM7409_ERR	7409	/* Internal Error, report to Faircom. */
#define	INT_MEM7410_ERR	7410	/* Internal Error, report to Faircom. */
#define	INT_MEM7411_ERR	7411	/* Internal Error, report to Faircom. */
#define	INT_MEM7412_ERR	7412	/* Internal Error, report to Faircom. */
#define	INT_MEM7413_ERR	7413	/* Internal Error, report to Faircom. */
#define	INT_MEM7414_ERR	7414	/* Internal Error, report to Faircom. */
#define	INT_MEM7414_ERR	7415	/* Internal Error, report to Faircom. */
#define	INT_MEM7416_ERR	7416	/* Internal Error, report to Faircom. */
#define	INT_MEM7417_ERR	7417	/* Internal Error, report to Faircom. */
#define	INT_MEM7418_ERR	7418	/* Internal Error, report to Faircom. */
#define	INT_MEM7419_ERR	7419	/* Internal Error, report to Faircom. */
#define	INT_MEM7420_ERR	7420	/* Internal Error, report to Faircom. */
#define	INT_MEM7421_ERR	7421	/* Internal Error, report to Faircom. */
#define	INT_MEM7422_ERR	7422	/* Internal Error, report to Faircom. */
#define	INT_MEM7423_ERR	7423	/* Internal Error, report to Faircom. */
#define	INT_MEM7424_ERR	7424	/* Internal Error, report to Faircom. */
#define	INT_MEM7425_ERR	7425	/* Internal Error, report to Faircom. */
#define	INT_MEM7426_ERR	7426	/* Internal Error, report to Faircom. */
#define	INT_MEM7427_ERR	7427	/* Internal Error, report to Faircom. */
#define	INT_MEM7428_ERR	7428	/* Internal Error, report to Faircom. */
#define	INT_MEM7429_ERR	7429	/* Internal Error, report to Faircom. */
#define	INT_MEM7430_ERR	7430	/* Internal Error, report to Faircom. */
#define	INT_MEM7431_ERR	7431	/* Internal Error, report to Faircom. */
#define	INT_MEM7432_ERR	7432	/* Internal Error, report to Faircom. */
#define	INT_MEM7433_ERR	7433	/* Internal Error, report to Faircom. */
#define	INT_MEM7434_ERR	7434	/* Internal Error, report to Faircom. */
#define	INT_MEM7435_ERR	7435	/* Internal Error, report to Faircom. */
#define	INT_MEM7436_ERR	7436	/* Internal Error, report to Faircom. */
#define	INT_MEM7437_ERR	7437	/* Internal Error, report to Faircom. */
#define	INT_MEM7438_ERR	7438	/* Internal Error, report to Faircom. */
#define	INT_MEM7439_ERR	7439	/* Internal Error, report to Faircom. */
#define	INT_MEM7440_ERR	7440	/* Internal Error, report to Faircom. */
#define	INT_MEM7441_ERR	7441	/* Internal Error, report to Faircom. */
#define	INT_MEM7442_ERR	7442	/* Internal Error, report to Faircom. */
#define	INT_MEM7443_ERR	7443	/* Internal Error, report to Faircom. */
#define	INT_MEM7444_ERR	7444	/* Internal Error, report to Faircom. */
#define	INT_MEM7445_ERR	7445	/* Internal Error, report to Faircom. */
#define	INT_MEM7446_ERR	7446	/* Internal Error, report to Faircom. */
#define	INT_MEM7447_ERR	7447	/* Internal Error, report to Faircom. */
#define	INT_MEM7448_ERR	7448	/* Internal Error, report to Faircom. */
#define	INT_MEM7449_ERR	7449	/* Internal Error, report to Faircom. */
#define	INT_MEM7450_ERR	7450	/* Internal Error, report to Faircom. */
#define	INT_MEM7451_ERR	7451	/* Internal Error, report to Faircom. */
#define	INT_MEM7452_ERR	7452	/* Internal Error, report to Faircom. */
#define	INT_MEM7453_ERR	7453	/* Internal Error, report to Faircom. */
#define	INT_MEM7454_ERR	7454	/* Internal Error, report to Faircom. */
#define	INT_MEM7455_ERR	7455	/* Internal Error, report to Faircom. */
#define	INT_MEM7456_ERR	7456	/* Internal Error, report to Faircom. */
#define	INT_MEM7457_ERR	7457	/* Internal Error, report to Faircom. */
#define	INT_MEM7458_ERR	7458	/* Internal Error, report to Faircom. */
#define	INT_MEM7459_ERR	7459	/* Internal Error, report to Faircom. */
#define	INT_MEM7460_ERR	7460	/* Internal Error, report to Faircom. */
#define	INT_MEM7461_ERR	7461	/* Internal Error, report to Faircom. */
#define	INT_MEM7462_ERR	7462	/* Internal Error, report to Faircom. */
#define	INT_MEM7463_ERR	7463	/* Internal Error, report to Faircom. */
#define	INT_MEM7464_ERR	7464	/* Internal Error, report to Faircom. */
#define	INT_MEM7467_ERR	7467	/* Internal Error, report to Faircom. */
#define	INT_MEM7468_ERR	7468	/* Internal Error, report to Faircom. */
#define	INT_MEM7469_ERR	7469	/* Internal Error, report to Faircom. */
#define	INT_MEM7470_ERR	7470	/* Internal Error, report to Faircom. */
#define	INT_MEM7471_ERR	7471	/* Internal Error, report to Faircom. */
#define	INT_MEM7472_ERR	7472	/* Internal Error, report to Faircom. */
#define	INT_MEM7473_ERR	7473	/* Internal Error, report to Faircom. */
#define	INT_MEM7474_ERR	7474	/* Internal Error, report to Faircom. */
#define	INT_MEM7475_ERR	7475	/* Internal Error, report to Faircom. */
#define	INT_MEM7476_ERR	7476	/* Internal Error, report to Faircom. */
#define	INT_MEM7477_ERR	7477	/* Internal Error, report to Faircom. */
#define	INT_MEM7478_ERR	7478	/* Internal Error, report to Faircom. */
#define	INT_MEM7479_ERR	7479	/* Internal Error, report to Faircom. */
#define	INT_MEM7480_ERR	7480	/* Internal Error, report to Faircom. */
#define	INT_MEM7481_ERR	7481	/* Internal Error, report to Faircom. */
#define	INT_MEM7482_ERR	7472	/* Internal Error, report to Faircom. */
#define	INT_MEM7483_ERR	7473	/* Internal Error, report to Faircom. */
#define	INT_MEM7484_ERR	7474	/* Internal Error, report to Faircom. */
#define	INT_MEM7485_ERR	7475	/* Internal Error, report to Faircom. */
#define	INT_MEM7486_ERR	7476	/* Internal Error, report to Faircom. */
#define	INT_MEM7487_ERR	7487	/* Internal Error, report to Faircom. */
#define	INT_MEM7488_ERR	7488	/* Internal Error, report to Faircom. */
#define	INT_MEM7489_ERR	7489	/* Internal Error, report to Faircom. */
#define	INT_MEMREQOOB_ERR	7490	/* A request for memory beyond reasonable limits. */
#define	INT_MEMRETOOB_ERR	7491	/* Attempting to return memory carrying an unreasonable large length value in its control header. */
#define	INT_MEMINVAVL_ERR	7492	/* Encountered an invalid “availability” counter during a sub-allocator get operation. */
#define	INT_MEMINVAVLRET_ERR	7493	/* An invalid “availability” counter while returning a block of memory. */
#define	INT_MEMINVHP_ERR	7494	/* An invalid header pointer for an allocation block. */
#define	INT_MEMINVLST_ERR	7495	/* A list connected with c-tree’s memory sub-allocator has become invalid or corrupted. */
#define	INT_MEMSWPFL_ERR	7496	/* Failure in memory swapping operation. */
#define	INT_MEMZRRET_ERR	7497	/* Attempting to return memory carrying a zero length in its control header. */
#define	INT_MEMINVSMOWN_ERR	7498	/* An invalid semaphore owner while getting memory. */
#define	INT_MEMINVSMOWNRT_ERR	7499	/* An invalid semaphore owner while returning memory. */

#endif /* ~ctIERRH */

/* end of ctierr.h */
