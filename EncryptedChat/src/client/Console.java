package client;

import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

import kernel.FileData;

public class Console {

	private static Logger log;
	private static UserStatus status = UserStatus.getInstance();
	static{
		log = Logger.getLogger("client.Console");
	}
	
	static void help()
	{
		System.out.println("注册新用户             reg     name    pass");
		System.out.println("登录                         login   name    pass");
		System.out.println("向好友发消息         talk    FID     message");
		System.out.println("修改好友备注         renf    FID     newName");
		System.out.println("配置IP和端口        conf    IP      port");
		System.out.println("给好友发文件         file    FID     filepath");
		System.out.println("重命名当前用户     ren     newName");
		System.out.println("添加好友                 addf    FID");
		System.out.println("删除好友                 delf    FID");
		System.out.println("登出                         logoff");
		System.out.println("打印用户信息         list");
		System.out.println("退出                         exit");
	}
	static void ListStatus()
	{
		System.out.println("**当前用户信息**");
		System.out.println(status.toString());
		System.out.println("*************");
	}
	static void showPrompt()
	{
		System.out.println();
		System.out.print((status.getName() != null?status.getName():"")+"#");
	}
	public static void main(String[] args) {
		status.startListeningThread();
		Scanner cmdin = new Scanner(System.in);
		showPrompt();
		String cmd = cmdin.nextLine();
		String[] arg = cmd.trim().split("\\s+");
		while (!arg[0].equals("exit")) {
			if (arg[0].equals("reg")) {
				String name = arg[1];
				String pass = arg[2];
				if(UserAction.Register(name, pass))
					log.log(Level.INFO, "用户(" + name + ")注册成功！");
				else
					log.log(Level.SEVERE, "用户(" + name + ")注册失败！");
			}
			else if (arg[0].equals("login")) {
				String name = arg[1];
				String pass = arg[2];
				UserAction.Login(name, pass);
			}
			else if (arg[0].equals("addf")) {
				int uid = Integer.parseInt(arg[1]);
				UserAction.AddFriend(uid);
			}
			else if (arg[0].equals("delf")) {
				int uid = Integer.parseInt(arg[1]);
				UserAction.DeleteFriend(uid);
			}
			else if (arg[0].equals("renf")) {
				int uid = Integer.parseInt(arg[1]);
				String fresh = arg[2]; 
				UserAction.RenameFriend(uid, fresh);
			}
			else if (arg[0].equals("ren")) {
				String fresh = arg[1];
				UserAction.Rename(fresh);
			}
			else if (arg[0].equals("list")) {
				ListStatus();
			}
			else if (arg[0].equals("talk")) {
				int uid = Integer.parseInt(arg[1]);
				String msg = arg[2];
				UserAction.SendMessage(uid, msg);
			}
			else if (arg[0].equals("file")) {
                int uid = Integer.parseInt(arg[1]);
                String path = arg[2];
                UserAction.SendMessage(uid, new FileData(path));
            }
			else if (arg[0].equals("conf")) {
                Configure.client_ip = arg[1];
			    Configure.client_port = Integer.parseInt(arg[2]);
            }
			else if (arg[0].equals("logoff")) {
				UserAction.Logoff();
			}
			else
				help();
			showPrompt();
			cmd = cmdin.nextLine();
			arg = cmd.trim().split("\\s+");
		}
		cmdin.close();
	}
}
