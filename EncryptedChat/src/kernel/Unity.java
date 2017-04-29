package kernel;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

//常用的工具函数
public class Unity {

	//从字节流中恢复对象
	public static Object BytesToObject(byte[] data)
	{
		ByteArrayInputStream bis = new ByteArrayInputStream(data);
		try {
			ObjectInputStream ois = new ObjectInputStream(bis);
			Object ret = ois.readObject();
			return ret;
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	//将对象转化成字节流
	public static byte[] ObjectToBytes(Object obj)
	{
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		try {
			ObjectOutputStream oos = new ObjectOutputStream(bos);
			oos.writeObject(obj);
			return bos.toByteArray();
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
	}
}
