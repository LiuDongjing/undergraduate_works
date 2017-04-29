package client;

import java.io.IOException;
import java.util.Properties;

public class Configure {

	static String server_ip;
	static int server_port;
	
	public static String client_ip;
	public static int client_port;
	static int client_port_spare;
	static{
		Properties prop = new Properties();
		try {
			prop.load(Configure.class.getResourceAsStream("configure.properties"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		server_ip = prop.getProperty("server.ip");
		server_port = Integer.parseInt(prop.getProperty("server.port"));
		
		client_ip = prop.getProperty("client.ip");
		client_port = Integer.parseInt(prop.getProperty("client.port"));
		client_port_spare = Integer.parseInt(prop.getProperty("client.port.spare"));
	}
}
