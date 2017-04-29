package kernel;
import java.io.Serializable;
//网上通信的数据包
public class Session implements Serializable{

    private static final long serialVersionUID = -2266512930205400969L;
	public CommandEnum command;//必须；指令
	public Object data;//可选；附带的数据
	public int from;//可选；数据的发送方
	public Session()
	{
		command = null;
		data = null;
	}
	
	public Session(CommandEnum c)
	{
		command = c;
		data = null;
	}
	
	public Session(CommandEnum c, Object d)
	{
		command = c;
		data = d;
	}
	public Session(CommandEnum c, Object d, int f)
	{
		command = c;
		data = d;
		from = f;
	}
}
