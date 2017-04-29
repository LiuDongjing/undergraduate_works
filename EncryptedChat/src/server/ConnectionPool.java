/*
 * 实现数据库连接池
 * */
package server;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
public class ConnectionPool {

	static Vector<Connection> pool;
	static Vector<Boolean> state;
	static final int PoolSize = Configure.mariaDB_poolsize;
	
	static Logger log;
	
	static final String url = "jdbc:mysql://"
			+Configure.mariaDB_ip
			+":"
			+Configure.mariaDB_port
			+"/"
			+Configure.mariaDB_database
			+"?user="
			+Configure.mariaDB_user
			+"&password="
			+Configure.mariaDB_password
			+"&useUnicode=true&characterEncoding=UTF8";
	
	static{
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		log = Logger.getLogger("server.ConnectionPool.static");
		
		pool = new Vector<Connection>(PoolSize);
		state = new Vector<Boolean>(PoolSize);
		for(int i=0;i < PoolSize;i++)
		{
			try {
				pool.add(i, DriverManager.getConnection(url));
				state.add(i, new Boolean(true));
			} catch (SQLException e) {
				state.add(i, new Boolean(false));
				e.printStackTrace();
			}
		}
	}
	static synchronized Connection getConnection()
	{
		Connection conn = null;
		for(int i = 0;i < PoolSize;i++)
		{
			if(state.elementAt(i).booleanValue())
			{
				conn = pool.elementAt(i);
				state.add(i, new Boolean(false));
				break;
			}
		}
		if(conn == null)
		{
			log.log(Level.SEVERE, "数据库连接池中无有效连接！系统退出！");
			System.exit(1);
		}
		return conn;
	}
	
	static synchronized void returnConnection(Connection conn)
	{
		for(int i = 0;i < PoolSize;i++)
		{
			if(conn == pool.elementAt(i))
			{
				state.add(i, new Boolean(true));
				return;
			}
		}
		try {
			conn.close();
			log.log(Level.WARNING, "释放一个不在池中的数据库连接！");
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}
