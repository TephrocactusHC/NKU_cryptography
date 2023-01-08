$\color{red}{NKU同学参考的话请给STAR}$
# 说明
本仓库包含了密码学课程的五个实验的代码和报告。本科的代码貌似年年都换，每年都不太一样，但是不会出圈，因此我都传上来一些。主要提供了一些前人的代码（不一定对，不一定能跑）。因此，本仓库的所有代码仅供参考。

# 友链
同时提供一些友链，大家可以自己参考看一看。
- [友链1](https://github.com/wanghanwei8/Crypto)
- [友链2](https://github.com/nkuwhjhhh/nku-cryptology)
- [友链3](https://github.com/kypomon/NKU_cryptography_project)
- [友链4](https://github.com/shesl-meow/nkcrypto)
- [友链5](https://github.com/caijiqhx/crypto_lab)
- [友链6](https://github.com/Rainefly/Cryptology)
# WARNING!
千万不要试图运行本仓库的代码，也不要试图看懂逻辑后复现，更不要试图在此基础上修改以期望得到正确代码。

# NOTICE!
注意，这里的代码都是我智慧的残渣，因为基本上每个年级到了本学期的课都实在是太多了，因此大多数的代码都不具有原创性，而且很多代码故意糊弄，不一定能跑。**因此，尤其不要直接COPY下来提交，这会使你陷入万劫不复的境地。**

# 本课复习资料
老规矩，在NKUG网自救资料那个仓库里。

# 大作业
上传了我的作业和参考文件


```mermaid
sequenceDiagram
opt 使用RSA算法进行AES密钥分发
note over A(client端),B(server端):双方已经通过某种密钥分发方式得到对付的RSA公钥和自己的公钥、私钥
A(client端)->>B(server端):A用B的RSA公钥使用RSA算法加密自己的AES密钥
note over A(client端),B(server端):B接收到加密后的A的AES密钥，用自己的RSA私钥解密，得到A的AES密钥
B(server端)->>A(client端):B用A的RSA公钥使用RSA算法加密自己的AES密钥
note over A(client端),B(server端):A接收到加密后的B的AES密钥，用自己的RSA私钥解密，得到B的AES密钥
end
opt 加密聊天（多线程编程，支持随意发送和接收）
note over A(client端),B(server端):双方使用对方的AES密钥加密消息后发送,收到消息后用自己的密钥进行解密
A(client端)->>B(server端):用B的AES密钥加密后发送消息
B(server端)->>A(client端):B接收后用自己的密钥解密，并可以用A的AES密钥解密消息后发送给A
note over A(client端),B(server端): .........
A(client端)->>B(server端):加密聊天
B(server端)->>A(client端):加密聊天
end
opt 断开连接
A(client端)->>B(server端):某一端发送"imquit"字段，这里以A为例
note over A(client端),B(server端):双方结束聊天
end
```
