# QT5_C-plus-plus-IoT-Device-Monitoring-Simulation-Project
QT5 + C++ 物聯網裝置監控模擬專案（個人版）

o	建置環境需求（QT版本、OS版本）
QT 5.14.2 以上版本
Windows 7 32位元 或 64位元 以上版本
OpenSSL 1.1.1.1 以上版本
Python 3.9 以上版本
Python Flask 3.1.x 版本

o	專案簡介
模擬IOT互聯網設備連線，
透過HTTP server獲取裝置的數據，
透過QT C++使用內建的Network Lib建立API連線，
由於QT5版本沒有HTTP Server Lib，
本人透過Python Flask建立HTTP Server API服務，
讀取設備的Json資訊顯示在視窗上，
並且設有定時詢問，
溫度異常提示、中斷提示。

o	本機編譯步驟
由於透過Python Flask需要先安裝Python與Flask
以下為Flask安裝指令
pip install flask
pip install flask_migrate
pip install flask_restx
pip install Flask-RESTx
pip install flask_sqlalchemy

執行QT程式前
1.需要確認mainwindow.cpp內"url.setUrl("http://127.0.0.1:5000/");"是否需要修改：
這邊是使用flask預設內部的IP與Port，
有測試過外部IP與網址也是可以使用。
2.需要確認dbdatabase.cpp內"db.setDatabaseName("D:\\QT_C++_Project\\IoT-Device-Monitoring-Simulation\\test.db");"是否需要修改：
這邊是資料庫是使用我的專案測試路徑，
測試中是使用絕對路徑。

程式結構
Sources
-main.cpp 主程式
-mainwindow.cpp 主視窗程式
-apiclient.cpp 網路API連線獲取Json
-dbdatabase.cpp 資料庫連結、新增資料
-warningwindow.cpp 警告視窗
Python Flask
-app.py 提供HTTP Server RESTful API服務
-data.json 裝置數據儲存Json檔
Database
-test.db 測試用SQLite QT5資料表

Http Server RESTful API功能查詢
![image](https://github.com/user-attachments/assets/cd458b36-1c37-453e-af6e-209b6d72e1a4)

o	測試方式說明
1.執行QT Project 建置Debug
![image](https://github.com/user-attachments/assets/41104fce-9775-41ee-864a-db587444f8fb)
未連線HTTP Server RESTful API
會顯示未連線並跳警告視窗

2.執行Python Flask
直接執行app.py 或者CMD指令 "python -m flask run --host=0.0.0.0 --debug"
連接HTTP Server讀取裝置Json數據
![image](https://github.com/user-attachments/assets/c00c6578-447c-41c8-af14-e2c971e9318b)

3.裝置異常會跳警告視窗如上圖，
設定有5秒自動更新數據與警告視窗偵測。

4.關掉app.py會因為連不到HTTP Server
![image](https://github.com/user-attachments/assets/41104fce-9775-41ee-864a-db587444f8fb)

5.只要有收到裝置Json數據就會記錄到資料庫
![image](https://github.com/user-attachments/assets/3c0ac034-da8f-43f5-90ca-380f5cb2efed)



參考
QT documentation 
https://doc.qt.io/qt-5/classes.html
Flask
https://flask.palletsprojects.com/zh-cn/stable/installation/
