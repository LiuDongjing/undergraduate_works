package kernel;
import java.io.Serializable;

//用户的信息
public class User implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = -2499364971798426980L;

	private String name;	//名称
	private String password;//密码
	private byte[] passwordMD5;//密码的MD5值
	private String ip;	//ip
	private int port;	//端口
	public User(String n, String p)
	{
		name = n;
		password = p;
		ip = "";
		port = 0;
		CipherBase cip = new TDEA();
		passwordMD5 = cip.calcMD5(p.getBytes());
	}
	
	public User(String n, String p, String i, int po)
	{
		this(n, p);
		ip = i;
		port = po;
	}
	
	public String getName()
	{
		return name;
	}
	
	public String getPassword()
	{
		return password;
	}
	public byte[] passwordMD5()
	{
		return passwordMD5;
	}
	public String getIp()
	{
		return ip;
	}
	public int getPort()
	{
		return port;
	}
}
