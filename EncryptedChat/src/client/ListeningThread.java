package client;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ListeningThread implements Runnable{
	
	private Thread thread;
	private boolean flag;
	private static Logger log = Logger.getLogger("client.Dispatcher");
	private static UserStatus status = UserStatus.getInstance();
	private Object lock;
	static byte[] parseIP(String ip)
	{
		String[] temp = ip.trim().split("\\.");
		byte[] dat = new byte[temp.length];
		for(int i = 0;i < temp.length;i++)
			dat[i] = (byte)Integer.parseInt(temp[i]);
		return dat;
	}
	
	public ListeningThread()
	{
		thread = new Thread(this);
		flag = true;
		lock = new Object();
		thread.start();
	}
	
	//有两个地址可供绑定
	public void run()
	{
		ServerSocket server = null;
		
		try {
			server = new ServerSocket();
		} catch (IOException e) {
			log.log(Level.SEVERE, e.getMessage());
		}
		try {
            server.setSoTimeout(100);
        } catch (SocketException e2) {
            e2.printStackTrace();
        }
		try {
			server.bind(new InetSocketAddress(InetAddress.getByAddress(parseIP(Configure.client_ip)), Configure.client_port));
			status.setIP(Configure.client_ip);
			status.setPort(Configure.client_port);
		} catch (UnknownHostException e) {
			log.log(Level.SEVERE, e.getMessage());
		} catch (IOException e) {
			try {
				server.bind(new InetSocketAddress(InetAddress.getByAddress(parseIP(Configure.client_ip)), Configure.client_port_spare));
				status.setIP(Configure.client_ip);
				status.setPort(Configure.client_port_spare);
			} catch (UnknownHostException e1) {
				log.log(Level.SEVERE, e1.getMessage());
			} catch (IOException e1) {
				log.log(Level.SEVERE, e1.getMessage());
			}
		}
		
		while(flag)
		{
			try {
				//socket由新线程关闭
				Socket socket = server.accept();
				new DispatchThread(socket);
			} catch(SocketTimeoutException ste)
			{
			    
			}
			catch (IOException e) {
				log.log(Level.SEVERE, e.getMessage());
			}
			if(!flag)
			{
			    try {
                    server.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
			    
			    //ServerSocket已关闭；通知等待的线程
			    synchronized(lock)
			    {
			        lock.notify();
			    }
			}
		}
	}

	public void kill()
	{
		flag = false;
		
		//同步；等待ServerSocket关闭
		synchronized(lock)
        {
            try {
                lock.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
	}
}
