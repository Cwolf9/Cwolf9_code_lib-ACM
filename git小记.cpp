/*
echo>a.txt
touch you.txt
ctrl+ins
shift+ins

check:
git config -l
git --version

create a repository:
git init
git init test2
git clone https://
git clone https://  test3

look dir:
dir/a
cd..
cd \
cls
ctrl+L

git status

let modify to stage(staged):
git add .
git add XXX.txt(file name)
submit version:
git commit -m "sth"

check version records:
git log
q
j
k
Enter
git log -p
git log --oneline
git log --oneline --all
git log --all --graph

return history version:
git checkout a1d634e
(commmit code)
return last version:
git checkout -

combine command
&&

add tag:
git tag -a name -m "BeiZhu"
git tag
git tag -a v0.5 -m "xiande" 75958e4

git show v0.5

git checkout v1

branch:

git branch branchName
git checkout branchName
git checkout master
create and goto branch:
git checkout -b branchName

git merge branchName


function: fire fighting


remote repository:

git remote add name address
git remote
git remote -v

上传代码:
git push -u remoteName branchName

git clone https://github.com/Cwolf9/retest
git clone https://github.com/Cwolf9/retest whh

获取远程更新:
git pull

git pull == git fetch && git merge


*/


/*

git log 中文乱码问题：
git bash 右键选择options->Text:
Locale:zh_CN charector set:UTF-8
git bash 输入命令:
git config --global i18n.commitencoding utf-8
git config --global i18n.logoutputencoding utf-8

https://blog.csdn.net/qq_27258799/article/details/78977764
https://www.jianshu.com/p/e11cdfe1733d
https://blog.zengrong.net/post/1249.html
https://blog.csdn.net/xl_lx/article/details/78223349
https://www.cnblogs.com/30go/p/8643459.html




这一两刚刚下载Git Bash，跟着慕课网学习node.js。
在视屏中用Git Bash时复制一段代码，我试着写，结果发现根本用不了Ctrl+C和Ctrl+V来复制和粘贴。
我就上网找，网上的答案都是在Git Bash的options（选项）里的properties，
然后在quickedit上打上钩，就行了。
我找了半天，根本找不到QAQ，再尝试了几次，发现在代码行右击后就有复制和粘贴选项，
只不过换了组合键
Ctrl+ins  复制
Shift+ins 粘贴

cmd命令行窗口显示中文乱码，多是因为cmd命令行窗口字符编码不匹配导致。

修改cmd窗口字符编码为UTF-8，命令行中执行：chcp 65001
切换回中文：chcp 936
这两条命令只在当前窗口生效，重启后恢复之前的编码。

切换cmd窗口字符编码有风险，例如切换过以后中文显示乱码，并且不能永久切换回原来模式，
只能每次chcp 936。

cmd中文显示乱码永久解决方案，以切换回中文936为例：

打开不正常的 CMD命令提示符窗口后,单击窗口左上角的图标，选择弹出的菜单中的“默认值”，
切换到第一个“选项”tab,将默认的代码页改为 936 后重启 CMD。重启cmd后还不能正常显示
请继续往下看。

如果重启 CMD以后无法生效：窗口的“默认值”和“属性”没变，则进入注册表，
在 HKEY_CURRENT_USER\Console下找到%SystemRoot%_system32_cmd.exe
（如果没有codepage就不考虑了），codepage值改为 936（十进制）或 3a8（十六进制）。
936(十进制)是简体中文的，如是其它语言，则改为对应的代码。

部分字符编码对应代码：
65001——UTF-8
936——简体中文
950——繁体中文
437——美国/加拿大英语
932——日文
949——韩文
866——俄文

最后一个乱码原因：CMD 的“默认值”或“属性”窗口的“字体”选项卡中设定为可以显示中文字符的字体，并且确定字体文件没有被破坏，字体最好设置为默认的点阵字体。



*/
/*
linux创建文件、文件夹:
touch name
mkdir name
vi name.txt
windows:
md c:\test\myfolder
md myfolder
mkdir folder
rd /s /q c:\test\myfolder
rd myfolder

type nul>a.txt
echo myname>b.txt
echo myname>>b.txt
del a.txt

*/