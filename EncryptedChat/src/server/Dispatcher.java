package server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

import kernel.CipherBase;
import kernel.CipherSimple;
import kernel.CommandEnum;
import kernel.NSSKAtoB;
import kernel.NSSKAtoS;
import kernel.NSSKStoA;
import kernel.Pair;
import kernel.Session;
import kernel.TDEA;
import kernel.Unity;
import kernel.User;

public class Dispatcher implements Runnable{

	private Thread thread;
	private Socket socket;
	private Logger log;
	private OnlineList userList;
	public Dispatcher(Socket s)
	{
		socket = s;
		log = Logger.getLogger("server.Dispatcher");
		userList = OnlineList.getInstance();
		thread = new Thread(this);
		thread.start();
	}
	@SuppressWarnings("unchecked")
	public void run()
	{
		ObjectInputStream objIns = null;
		try {
			objIns = new ObjectInputStream(socket.getInputStream());
		} catch (IOException e) {
			e.printStackTrace();
		}
		ObjectOutputStream objOuts = null;
		try {
			objOuts = new ObjectOutputStream(socket.getOutputStream());
		} catch (IOException e) {
			e.printStackTrace();
		}

		Session sess = null;
		boolean flag = true;
		try {
			sess = (Session)objIns.readObject();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			flag = false;
		} catch (IOException e) {
			e.printStackTrace();
			flag = false;
		}
		User data = null;
		Session retState = null;
		
		switch(sess.command)
		{
		case UserRegister:
			flag = true;
		    try {
				data = (User)objIns.readObject();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
				flag = false;
			} catch (IOException e) {
				e.printStackTrace();
				flag = false;
			}
			if(flag && (new DatabaseOperation().registerUser(data)))
				try {
					objOuts.writeObject(new Session(CommandEnum.Success));
				} catch (IOException e) {
					e.printStackTrace();
					flag = false;
				}
			if(!flag)
				try {
					objOuts.writeObject(new Session(CommandEnum.Failed));
				} catch (IOException e) {
					e.printStackTrace();
				}
			break;
		case UserLogin:
			flag = true;
		    try {
				data = (User)objIns.readObject();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
				flag = false;
			} catch (IOException e) {
				e.printStackTrace();
				flag = false;
			}
			retState = new Session();
			if(flag)
			    //查询数据库验证用户身份；需要的返回数据存在retState中
			    new DatabaseOperation().loginUser(data, retState);
			else
			    retState.command = CommandEnum.Failed;
			try {
				objOuts.writeObject(retState);
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case AddFriend:
			retState = new Session();
			@SuppressWarnings("unchecked")
			Pair<Integer, Integer> p = (Pair<Integer, Integer>)sess.data;
			//执行添加好友的操作，通过retState返回操作的状态
			new DatabaseOperation().addFriend(p.first().intValue(), p.second().intValue(), retState);
			try {
				objOuts.writeObject(retState);
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case RequestCommunication:
			NSSKAtoS nas = (NSSKAtoS)sess.data;
			retState = new Session(CommandEnum.Failed,
					"服务器端错误！");
			if(!userList.isUserOnline(nas.BID))
			{
				retState.data = "用户"+nas.BID+"不在线！";
			}
			else
			{
				//不检查两者是否是朋友关系
				AliveUser B = userList.getUser(nas.BID);
				CipherBase cip = new TDEA();
				
				//会话秘钥；K_AB
				byte[] skey = cip.genRandomKey();
				
				//未用K_AS加密的数据；即{N_A,K_AB,B,{K_AB,A}K_BS}
				NSSKStoA nsa = new NSSKStoA(
						nas.nonce, skey, nas.BID,
						B.ip, B.port, cip.encrypt(
								Unity.ObjectToBytes(new NSSKAtoB(skey, 
										nas.AID,
										nas.AIP,
										nas.APort)
										), B.pass));
				
				
				//A必须是已经登录了；最终的用K_AS加密后的数据
				retState.command = CommandEnum.Success;
				retState.data = cip.encrypt(Unity.ObjectToBytes(nsa), userList.getUser(nas.AID).pass);
				try {
					objOuts.writeObject(retState);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			break;
		case UserLogoff:
			if(flag)
			{
			    retState = new Session(CommandEnum.Success);
			    Integer id = (Integer)sess.data;
	            //将用户从在线用户列表中移除
			    userList.removeUser(id);
	            log.log(Level.INFO, "用户"+id+"已下线。");
			}
			else
			    retState = new Session(CommandEnum.Failed);
			try {
				objOuts.writeObject(retState);
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		case DelFriend:
			if(flag)
		    {
			    @SuppressWarnings("unchecked")
    			Pair<Integer, Integer> pr = (Pair<Integer, Integer>)sess.data;
    			try {
    				objOuts.writeObject(new DatabaseOperation().delFriend(pr));
    			} catch (IOException e2) {
    				e2.printStackTrace();
    			}
		    }
			else
			{
			    try {
                    objOuts.writeObject(new Session(CommandEnum.Failed));
                } catch (IOException e2) {
                    e2.printStackTrace();
                }
			}
			break;
		case RenameFriend:
			if(flag)
    		    try {
    				objOuts.writeObject(new DatabaseOperation().renameFriend(
    						(Pair<Integer, Pair<Integer, String>>)sess.data));
    			} catch (IOException e2) {
    				e2.printStackTrace();
    			}
			else
			    try {
                    objOuts.writeObject(new Session(CommandEnum.Failed));
                } catch (IOException e2) {
                    e2.printStackTrace();
                } 
			break;
		case Rename:
			if(flag)
    		    try {
    				objOuts.writeObject(new DatabaseOperation().rename(
    						(Pair<Integer, String>)sess.data));
    			} catch (IOException e2) {
    				e2.printStackTrace();
    			}
			else
			    try {
                    objOuts.writeObject(new Session(CommandEnum.Failed));
                } catch (IOException e2) {
                    e2.printStackTrace();
                }
			break;
		default:
			break;
		}
		try {
			objIns.close();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		try {
			objOuts.close();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		try {
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
