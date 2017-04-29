package server;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
public class Boot {

	public static void main(String[] args) {

		ServerSocket serverSocket = null;
		Socket socket = null;
		try {
			//在调用Configure静态类时，Configure的静态方法会加载配置文件
		    serverSocket = new ServerSocket(Configure.net_port);
		} catch (IOException e) {
			e.printStackTrace();
		}
		while(true)
		{
			try {
				socket = serverSocket.accept();
				//socket由新线程关闭
				new Dispatcher(socket);
			} catch (IOException e) {
				e.printStackTrace();
				break;
			}
		}
	}
}
