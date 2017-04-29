package kernel;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.Serializable;

//用于用户间传输文件
public class FileData  implements Serializable{

    private static final long serialVersionUID = 390460559643815877L;

    public String name;//文件名；不包括路径
    public byte[] data;//文件中的数据
    
    /*
     * 将两个字节数组组装成一个完成的数组
     * */
    private byte[] joinBytes(byte[] a, byte[] b, int len)
    {
        byte[] ret = null;
        if(a == null)
        {
            ret = new byte[len];
            System.arraycopy(b, 0, ret, 0, len);
        }
        else
        {
            ret = new byte[a.length+len];
            System.arraycopy(a, 0, ret, 0, a.length);
            System.arraycopy(b, 0, ret, a.length, len);
        }
        return ret;
    }
    
    //返回路径中的文件名
    private String parseName(String path)
    {
        String sep = System.getProperty("file.separator");
        return path.substring(path.lastIndexOf(sep)+1);
    }
    
    public FileData(String path)
    {
        name = parseName(path);
        byte[] buf = new byte[1024];
        try {
            BufferedInputStream bis = new BufferedInputStream(
                    new FileInputStream(path));
            int len = 0;
            while((len = bis.read(buf)) > 0)
                data = joinBytes(data, buf, len);
            bis.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public String toString()
    {
        writeFile();
        return "文件"+name+"已保存在当前目录";
    }
    
    //保存文件到当前目录
    public void writeFile()
    {
        try {
            BufferedOutputStream bos = new BufferedOutputStream(
                    new FileOutputStream(name));
            if(data != null && data.length > 0)
                bos.write(data);
            data = null;
            bos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
