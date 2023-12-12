import tkinter.filedialog
import tkinter.messagebox
import tkinter as tk
import threading
import hashlib
import socket
import time

import utils

#import locale
#locale.setlocale(locale.LC_CTYPE, "English_United States.932")

# 登录界面
# 功能描述：基于tkinter模块搭建，含有账号输入框、密码输入框、登录按钮、注册按钮。
class Login_win:
    def show(self):
        # 进入消息循环
        self.win.mainloop()

    def destroy(self):
        self.win.destroy()

    def __init__(self):
        self.win = tk.Tk()
        # tk.StringVar() 同时保证了值的变更随时可以显示在界面上
        self.user = tk.StringVar()
        self.pwd = tk.StringVar()

        # 总窗口配置
        self.win.geometry("440x280")
        self.win.title("登录")
        # 设置窗口是否可变长、宽，True：可变，False：不可变
        self.win.resizable(width=True, height=True)
        # 设置背景颜色
        # self.win.configure(background="#D1EDE1")

        # 左侧 账号文本 配置
        self.label1 = tk.Label(self.win)
        self.label1.place(relx=0.055, rely=0.1, height=31, width=89)
        self.label1.configure(text='账号')
        # 设置背景颜色
        # self.label1.configure(background="#7BC5AE")

        # 用户账号输入文本框 配置
        self.entry_user = tk.Entry(self.win)
        self.entry_user.place(relx=0.28, rely=0.11, height=26, relwidth=0.554)
        self.entry_user.configure(textvariable=self.user)
        # 设置背景颜色
        # self.entry_user.configure(background="#D1EDE9")

        # 左侧 密码文本 配置
        self.label2 = tk.Label(self.win)
        self.label2.place(relx=0.055, rely=0.27, height=31, width=89)
        self.label2.configure(text='密码')
        # 设置背景颜色
        # self.label2.configure(background="#7BC5AE")

        # 用户密码输入文本框 配置
        self.entry_pwd = tk.Entry(self.win)
        self.entry_pwd.place(relx=0.28, rely=0.28, height=26, relwidth=0.554)
        self.entry_pwd.configure(show="*")
        self.entry_pwd.configure(textvariable=self.pwd)
        # self.entry_pwd.configure(background="#D1EDE9")

        # 登录按钮 配置
        self.btn_login = tk.Button(self.win)
        self.btn_login.place(relx=0.13, rely=0.6, height=32, width=88)
        self.btn_login.configure(text='登录')
        # self.btn_login.configure(background="#7BC5AE")

        # 注册按钮 配置
        self.btn_reg = tk.Button(self.win)
        self.btn_reg.place(relx=0.6, rely=0.6, height=32, width=88)
        self.btn_reg.configure(text='注册')
        # self.btn_reg.configure(background="#7BC5AE")

# 聊天窗口界面
# 功能描述：基于tkinter模块搭建，含有其他已登录用户列表显示框、聊天记录显示框、发送消息输入框、发送消息按钮等。
class Main_win:
    closed_fun = None

    def show(self):
        # 进入消息循环
        self.win.mainloop()

    def destroy(self):
        try:
            self.closed_fun()
        except:
            pass
        self.win.destroy()

    # 构造方法，参数为按钮事件处理函数，从客户端main传进来，可以实现按钮回调
    def __init__(self):
        # 初始化参数实例变量，聊天室主页面
        self.win = tk.Tk()
        self.win.protocol('WM_DELETE_WINDOW', self.destroy)
        self.win.geometry("480x320")
        self.win.title("聊天室")
        self.win.resizable(width=True,height=True)

        self.msg = tk.StringVar()
        self.name = tk.StringVar()

        self.user_list = tk.Listbox(self.win)
        self.user_list.place(relx=0.75, rely=0.15, relheight=0.72, relwidth=0.23)

        self.label1 = tk.Label(self.win)
        self.label1.place(relx=0.76, rely=0.075, height=21, width=101)
        self.label1.configure(text='在线用户')

        self.history = tk.Text(self.win)
        self.history.place(relx=0.02, rely=0.24, relheight=0.63, relwidth=0.696)
        self.history.configure(state='disabled')

        self.entry_msg = tk.Entry(self.win)
        self.entry_msg.place(relx=0.02, rely=0.9, height=24, relwidth=0.59)
        self.entry_msg.configure(textvariable=self.msg)

        self.btn_send = tk.Button(self.win)
        self.btn_send.place(relx=0.62, rely=0.89, height=28, width=45)
        self.btn_send.configure(text='发送')

        self.label2 = tk.Label(self.win)
        self.label2.place(relx=0.24, rely=0.0, height=57, width=140)
        self.label2.configure(textvariable=self.name)

