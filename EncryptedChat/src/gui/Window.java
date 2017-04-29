package gui;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Color;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import java.awt.FlowLayout;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.border.MatteBorder;

import client.Configure;
import client.Friend;
import client.UserAction;
import client.UserStatus;

import javax.swing.AbstractAction;
import java.awt.event.ActionEvent;
import javax.swing.Action;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.logging.Logger;
import javax.swing.DefaultListModel;
import javax.swing.JPasswordField;
import javax.swing.ListSelectionModel;
import javax.swing.JScrollPane;

public class Window extends JFrame {

    private static final long serialVersionUID = -1073765251125725011L;
    private JPanel contentPane;
    private JTextField userName;
    private final Action action = new SwingAction();
    private final Action action_1 = new SwingAction_1();
    private JPasswordField pass;
    private final Action action_2 = new SwingAction_2();

    private JTextArea inputText;
    private JList<String> friendList;
    private DefaultListModel<String> friendListModel;
    private JLabel title;
    
    private static Logger log = Logger.getLogger("gui.Window");
    private static UserStatus status = UserStatus.getInstance();

    private HashMap<Integer,Integer> indexToId;
    private JTextArea msgLog;
    private final Action action_3 = new SwingAction_3();
    /**
     * 程序入口
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    Window frame = new Window();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    
    public Window() {
        status.setClientType(1);
        status.setWindow(this);
        setResizable(false);
        setTitle("局域网聊天系统");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 621, 375);
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        setContentPane(contentPane);
        contentPane.setLayout(null);
        
        JPanel panel = new JPanel();
        panel.setBounds(5, 5, 600, 26);
        panel.setBorder(new MatteBorder(1, 0, 1, 0, (Color) new Color(0, 0, 0)));
        contentPane.add(panel);
        panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
        
        title = new JLabel("欢迎");
        panel.add(title);
        
        friendListModel = new DefaultListModel<String>();
        
        JPanel panel_1 = new JPanel();
        panel_1.setBounds(5, 302, 600, 34);
        panel_1.setBorder(new MatteBorder(1, 0, 1, 0, (Color) new Color(0, 0, 0)));
        contentPane.add(panel_1);
        panel_1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
        
        JLabel label = new JLabel("用户名：");
        panel_1.add(label);
        
        userName = new JTextField();
        panel_1.add(userName);
        userName.setColumns(10);
        
        JLabel label_1 = new JLabel("    密码：");
        panel_1.add(label_1);
        
        pass = new JPasswordField();
        pass.setColumns(10);
        panel_1.add(pass);
        
        JButton button = new JButton("登录");
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                login();
            }
        });
        button.setAction(action);
        panel_1.add(button);
        
        JButton button_1 = new JButton("注册");
        button_1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                register();
            }
        });
        button_1.setAction(action_1);
        panel_1.add(button_1);
        
        JButton button_3 = new JButton("配置");
        button_3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                config();
            }
        });
        button_3.setAction(action_3);
        panel_1.add(button_3);
        
        JPanel panel_2 = new JPanel();
        panel_2.setBorder(new MatteBorder(1, 1, 1, 1, (Color) new Color(0, 0, 0)));
        panel_2.setBounds(154, 41, 451, 251);
        contentPane.add(panel_2);
        panel_2.setLayout(null);
        
        JButton button_2 = new JButton("发送");
        button_2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                sendMessage();
            }
        });
        button_2.setAction(action_2);
        button_2.setBounds(343, 174, 98, 66);
        panel_2.add(button_2);
        
        JScrollPane scrollPane = new JScrollPane();
        scrollPane.setBounds(10, 174, 323, 66);
        panel_2.add(scrollPane);
        
        inputText = new JTextArea();
        scrollPane.setViewportView(inputText);
        
        JScrollPane scrollPane_1 = new JScrollPane();
        scrollPane_1.setBounds(10, 10, 431, 154);
        panel_2.add(scrollPane_1);
        
        msgLog = new JTextArea();
        msgLog.setEditable(false);
        scrollPane_1.setViewportView(msgLog);
        msgLog.setRows(4);
        
        JScrollPane scrollPane_2 = new JScrollPane();
        scrollPane_2.setBounds(5, 41, 139, 251);
        contentPane.add(scrollPane_2);
        friendList = new JList<String>(friendListModel);
        scrollPane_2.setViewportView(friendList);
        friendList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        friendList.setBorder(new MatteBorder(1, 1, 1, 1, (Color) new Color(0, 0, 0)));
        
        //关闭窗口的时候退出当前账号
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                if(JOptionPane.NO_OPTION == 
                        JOptionPane.showConfirmDialog(null, "确认退出吗？", "确认", JOptionPane.YES_NO_OPTION))
                    setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
                else
                {
                    if(status.isOnline())
                        UserAction.Logoff();
                    setDefaultCloseOperation(EXIT_ON_CLOSE);
                }
            }
          });
    }

    private class SwingAction extends AbstractAction {
        public SwingAction() {
            putValue(NAME, "登录");
            putValue(SHORT_DESCRIPTION, "登录系统");
        }
        public void actionPerformed(ActionEvent e) {
        }
    }
    private class SwingAction_1 extends AbstractAction {
        public SwingAction_1() {
            putValue(NAME, "注册");
            putValue(SHORT_DESCRIPTION, "注册新账户");
        }
        public void actionPerformed(ActionEvent e) {
        }
    }
    private class SwingAction_2 extends AbstractAction {
        public SwingAction_2() {
            putValue(NAME, "发送");
            putValue(SHORT_DESCRIPTION, "发送消息");
        }
        public void actionPerformed(ActionEvent e) {
        }
    }
    private void login()
    {
        String name = userName.getText();
        @SuppressWarnings("deprecation")
        String password = pass.getText();
        if(name.equals("") || password.equals(""))
        {
            JOptionPane.showMessageDialog(null, "请填写用户名和密码！", "错误", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if(!UserAction.Login(name, password))
        {
            JOptionPane.showMessageDialog(null, "登录失败！", "错误", JOptionPane.ERROR_MESSAGE);
            return;
        }
        title.setText(name+"，你好！欢迎登录局域网聊天系统~~");
        indexToId = new HashMap<Integer, Integer>();
        int index = 0;
        for(Entry<Integer,Friend> e:status.getFriends().entrySet())
        {
            friendListModel.add(index, e.getValue().remark);
            indexToId.put(new Integer(index), e.getKey());
            index++;
        }
    }
    public void register()
    {
        String name = userName.getText();
        @SuppressWarnings("deprecation")
        String password = pass.getText();
        if(name.equals("") || password.equals(""))
        {
            JOptionPane.showMessageDialog(null, "请填写用户名和密码！", "错误", JOptionPane.ERROR_MESSAGE);
            return;
        }
        if(JOptionPane.NO_OPTION == 
                JOptionPane.showConfirmDialog(null, "用户名是："+name+"；密码是："+password, "确认", JOptionPane.YES_NO_OPTION))
            return;
        if(UserAction.Register(name, password))
            JOptionPane.showMessageDialog(null,"用户"+name+"注册成功！", "信息", JOptionPane.INFORMATION_MESSAGE);
        else
            JOptionPane.showMessageDialog(null, "注册失败！", "错误", JOptionPane.ERROR_MESSAGE);
    }
    public void newMessage(int from, Object msg)
    {
        Friend f = status.getFriends().get(new Integer(from));
        String name = "陌生人";
        if(f != null)
            name = f.remark;
        msgLog.setText(msgLog.getText()+"\nfrom("+
            name+"):"+msg+"\n");
    }
    private void sendMessage()
    {
        if(!status.isOnline())
        {
            JOptionPane.showMessageDialog(null, "请先登录！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        String text = inputText.getText();
        if(text.length() == 0)
        {
            JOptionPane.showMessageDialog(null, "消息不能为空！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        int index = friendList.getSelectedIndex();
        if(index < 0)
        {
            JOptionPane.showMessageDialog(null, "请选择好友！","提示",JOptionPane.ERROR_MESSAGE);
            return;
        }
        Integer fid = indexToId.get(new Integer(index));
        if(!UserAction.SendMessage(fid.intValue(), text))
            JOptionPane.showMessageDialog(null, "消息发送失败！","提示",JOptionPane.ERROR_MESSAGE);
        else
        {
            msgLog.setText(msgLog.getText()+"\nto("+status.getFriends().get(fid).remark
                    +"):"+text+"\n");
            inputText.setText("");
        }
    }
    private void config()
    {
        String ip = JOptionPane.showInputDialog("本地IP：");
        if(ip != null && ip.length() > 0)
            Configure.client_ip = ip;
        String port = JOptionPane.showInputDialog("监听的端口：");
        if(port != null && port.length() > 0)
            Configure.client_port = Integer.parseInt(port);
    }
    private class SwingAction_3 extends AbstractAction {
        public SwingAction_3() {
            putValue(NAME, "配置");
            putValue(SHORT_DESCRIPTION, "配置IP和端口");
        }
        public void actionPerformed(ActionEvent e) {
        }
    }
}
