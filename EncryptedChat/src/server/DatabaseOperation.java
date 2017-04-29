package server;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

import kernel.CommandEnum;
import kernel.Pair;
import kernel.Session;
import kernel.User;

public class DatabaseOperation {

	private static Logger log = Logger.getLogger("server.DatabaseOperation");
	
	private static OnlineList userList = OnlineList.getInstance();
	
	static String bytesToMD5Hex(byte[] data)
	{
		String hex = "";
		String tab = "0123456789ABCDEF";
		for(int i=0;i < 16;i++)
		{
			byte e = 0;
			if(i < data.length)
				e = data[i];
			int high = (e >> 4) & 0x0F;
			int low = e & 0x0F;
			hex += tab.charAt(high);
			hex += tab.charAt(low);
		}
		return hex;
	}
	public boolean registerUser(User data)
	{
		Connection conn = ConnectionPool.getConnection();
		String sql = "insert into user(name,`key`) values('"
		+data.getName()+"',unhex('"
		+bytesToMD5Hex(data.passwordMD5())+
		"'))";
		Statement stmt = null;
		boolean state = true;
		try {
			stmt = conn.createStatement();
		} catch (SQLException e) {
			e.printStackTrace();
			state = false;
		}
		try {
			stmt.execute(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			state = false;
		}
		ConnectionPool.returnConnection(conn);
		return state;
	}
	
	public int loginUser(User user, Session sess)
	{
		Connection conn = ConnectionPool.getConnection();
		String sql = "select id from user where name='"
				+user.getName()+"' and `key`=unhex('"
				+bytesToMD5Hex(user.passwordMD5())
				+"')";
		Statement stmt = null;
		int state = 0;
		sess.data = "服务器端错误！";
		sess.command = CommandEnum.Failed;
		try {
			stmt = conn.createStatement();
		} catch (SQLException e) {
			log.log(Level.SEVERE, e.getMessage());
			state = 1;
		}
		try {
			ResultSet result = stmt.executeQuery(sql);
			if(result.next())
			{
				//登录成功
				int uid = result.getInt(1);
				if(!userList.isUserOnline(uid))
					userList.addUser(new AliveUser(uid, user));
				else
				{
					sess.data = "用户"+uid+"已在线！";
					ConnectionPool.returnConnection(conn);
					return 0;
				}
				sql = "select friend_id,remark from relation where user_id='"
						+uid+"'";
				ResultSet result0 = stmt.executeQuery(sql);
				HashMap<Integer,String> friendList = new HashMap<Integer,String>();
				while(result0.next())
				{
					friendList.put(new Integer(result0.getInt(1)), result0.getString(2));
				}
				sess.data = new Pair<Integer,HashMap<Integer,String>>(new Integer(uid), friendList);
				sess.command = CommandEnum.Success;
				log.log(Level.INFO, "用户" 
				+ user.getName() 
				+ "("
				+user.getIp()
				+":"
				+user.getPort()
				+")登录成功！");
			}
			else
			{
				//用户不存在或密码错误
				state = 2;
				sess.data = "用户不存在或密码错误！";
			}
		} catch (SQLException e) {
			log.log(Level.SEVERE, e.getMessage());
			state = 3;
		}
		ConnectionPool.returnConnection(conn);
		if(state != 0)
			log.log(Level.WARNING, "用户(" + user.getName() + ")登录失败！");
		return state;
	}
	
	public int addFriend(int myUID, int friendUID, Session sess)
	{
		if(myUID == friendUID)
		{
			sess.data = "不可添加自己为朋友！";
			sess.command = CommandEnum.Failed;
			return 3;
		}
		Connection conn = ConnectionPool.getConnection();
		String sql = null;
		Statement stmt = null;
		String friendName = null;
		int state = 0;
		sess.data = "服务器端错误！";
		sess.command = CommandEnum.Failed;
		try {
			stmt = conn.createStatement();
		} catch (SQLException e) {
			log.log(Level.SEVERE, e.getMessage());
			state = 1;
		}
		sql = "select count(*) from relation where user_id='"
				+myUID
				+"' and friend_id='"
				+friendUID
				+"'";
		try {
			ResultSet result = stmt.executeQuery(sql);
			if(result.next() && result.getInt(1) > 0)
			{
				//好友关系已存在
				state = 0;
				sess.data = "好友关系已存在！";
				sess.command = CommandEnum.Success;
				return state;
			}
		} catch (SQLException e) {
			log.log(Level.SEVERE, e.getMessage());
			state = 1;
		}
		
		sql = "select name from user where id='"
				+friendUID
				+"'";
		try {
			ResultSet result = stmt.executeQuery(sql);
			if(result.next())
			{
				friendName = result.getString(1);
				sql = "insert into relation(user_id,friend_id,remark) values('"
						+myUID+"','"
						+friendUID+"','"
						+friendName+"')";
				stmt.execute(sql);
				sess.data = "成功添加好友！";
				sess.command = CommandEnum.Success;
			}
			else
			{
				state = 2;
				sess.data = "用户"+friendUID+"不存在！";
			}
		} catch (SQLException e) {
			log.log(Level.SEVERE, e.getMessage());
			state = 1;
		}
		ConnectionPool.returnConnection(conn);
		return state;
	}

	public Session delFriend(Pair<Integer, Integer> pair)
	{
		String sql = "delete from relation where user_id='"
				+pair.first()
				+"' and friend_id='"
				+pair.second()
				+"'";
		Session ret = new Session(CommandEnum.Success);
		Connection conn = ConnectionPool.getConnection();
		try {
			Statement stmt = conn.createStatement();
			stmt.execute(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			ret.command = CommandEnum.Failed;
			ret.data = "数据库错误！";
		}
		ConnectionPool.returnConnection(conn);
		return ret;
	}
	
	public Session renameFriend(Pair<Integer, Pair<Integer, String>> pair)
	{
		String sql = "update relation set remark='"
				+pair.second().second()
				+"' where user_id = '"
				+pair.first()+
				"' and friend_id='"
				+pair.second().first()
				+"'";
		Session ret = new Session(CommandEnum.Success);
		Connection conn = ConnectionPool.getConnection();
		try {
			Statement stmt = conn.createStatement();
			stmt.execute(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			ret.command = CommandEnum.Failed;
			ret.data = "数据库错误！";
		}
		ConnectionPool.returnConnection(conn);
		return ret;
	}
	
	public Session rename(Pair<Integer, String> pair)
	{
		String sql = "update user set name='"
				+pair.second()
				+"' where id = '"
				+pair.first()
				+"'";
		Session ret = new Session(CommandEnum.Success);
		Connection conn = ConnectionPool.getConnection();
		try {
			Statement stmt = conn.createStatement();
			stmt.execute(sql);
		} catch (SQLException e) {
			e.printStackTrace();
			ret.command = CommandEnum.Failed;
			ret.data = "数据库错误！";
		}
		ConnectionPool.returnConnection(conn);
		return ret;
	}
}
