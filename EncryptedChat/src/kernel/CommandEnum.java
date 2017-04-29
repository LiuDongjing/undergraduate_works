package kernel;

//网上通信的指令
public enum CommandEnum {

	UserRegister,	//注册用户
	UserLogin,		//用户登录
	UserLogoff,		//用户下线
	AddFriend,		//添加好友
	DelFriend,		//删除好友
	RenameFriend,	//修改好友备注名
	Rename,			//重命名当前用户
	RequestCommunication,//NSSK协议的1-2步
	NotifyB,		//NSSK的3-5步
	SendMessage,	//向好友发送信息
	Success,		//操作成功
	Failed			//操作失败
}
