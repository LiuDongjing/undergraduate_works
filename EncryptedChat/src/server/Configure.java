package server;

import java.io.IOException;
import java.util.Properties;

public class Configure {

	static int net_port;
	
	static String mariaDB_ip;
	static int mariaDB_port;
	static String mariaDB_database;
	static String mariaDB_user;
	static String mariaDB_password;
	static int mariaDB_poolsize;
	static{
		Properties prop = new Properties();
		try {
			prop.load(Configure.class.getResourceAsStream("configure.properties"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		net_port = Integer.parseInt(prop.getProperty("net.port"));
		mariaDB_ip = prop.getProperty("mariaDB.ip");
		mariaDB_port = Integer.parseInt(prop.getProperty("mariaDB.port"));
		mariaDB_database = prop.getProperty("mariaDB.database");
		mariaDB_user = prop.getProperty("mariaDB.user");
		mariaDB_password = prop.getProperty("mariaDB.password");
		mariaDB_poolsize = Integer.parseInt(prop.getProperty("mariaDB.poolsize"));
	}
}
