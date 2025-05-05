import json
from flask import Flask,  request, jsonify
from flask_restx  import Api, Namespace, Resource, fields

app = Flask(__name__)
api = Api(app)

filename = 'data.json'
json_file  = open(filename, 'r')
data = json.loads(json_file.read())
json_file.close()

'''
data = 
{"device": [
{"name": "device1", "temp": "20", "rh": "100", "state": "test1", "date_time": "2025-05-01T12:00:00"},
 {"name": "device2", "temp": "30", "rh": "90", "state": "test2", "date_time": "2025-05-01T12:00:00"},
 {"name": "device3", "temp": "40", "rh": "50", "state": "test3", "date_time": "2025-05-01T12:00:00"},
 {"name": "device4", "temp": "50", "rh": "20", "state": "test4", "date_time": "2025-05-01T12:00:00"},
 {"name": "device5", "temp": "60", "rh": "0", "state": "test5", "date_time": "2025-05-01T12:00:00"}
 ]}

'''
'''
data = [{"name": "device1", "temp": "40", "rh": "80", "state": "test", "date_time": "2025-05-01T12:00:00"},
        {"name": "device2", "temp": "25", "rh": "70", "state": "test", "date_time": "2025-05-01T12:00:00"},
        {"name": "device3", "temp": "25", "rh": "70", "state": "test", "date_time": "2025-05-01T12:00:00"},
        {"name": "device4", "temp": "25", "rh": "70", "state": "test", "date_time": "2025-05-01T12:00:00"}, 
        {"name": "device5", "temp": "25", "rh": "70", "state": "test", "date_time": "2025-05-01T12:00:00"}
        ]
'''

# 定義一個模型
input_model = api.model('InputModel', {
    'name': fields.String(required=True, description='設備名'),
    'temp': fields.String(required=False, description='溫度'),
    'rh': fields.String(required=False, description='濕度', max=100, min=0),
    'state': fields.String(required=False, description='狀態'),
    'date_time': fields.String(required=False, description='資料時間'),
})


# 定義命名空間
test_get = Namespace("物聯網裝置監控模擬專案")
test_post = Namespace("物聯網裝置監控模擬專案")
test_put = Namespace("物聯網裝置監控模擬專案")

# 定義 RESTful 資源
@test_get.route("/hello/get")
class HelloWorld(Resource):
    @test_get.expect(input_model, validate=True)  # 使用模型定義預期的輸入
    def get(self):
        load = test_ns.payload  # 自動解析並驗證請求數據
        name = load['name']
        if name == "device1":
            return jsonify(data[0])
        if name == "device2":
            return jsonify(data[1])
        if name == "device3":
            return jsonify(data[2])
        if name == "device4":
            return jsonify(data[3])
        if name == "device5":
            return jsonify(data[4])
        if name == "all":
            return jsonify(data)

# 將命名空間加入 API
api.add_namespace(test_get, '/test')

# 定義 RESTful 資源
@test_get.route("/hello/get1")
class HelloWorld(Resource):
    def get(self):
        return jsonify(data[0])
# 將命名空間加入 API
api.add_namespace(test_get, '/test')

# 定義 RESTful 資源
@test_get.route("/hello/get2")
class HelloWorld(Resource):
    def get(self):
        return jsonify(data[1])
# 將命名空間加入 API
api.add_namespace(test_get, '/test')

# 定義 RESTful 資源
@test_get.route("/hello/get3")
class HelloWorld(Resource):
    def get(self):
        return jsonify(data[2])
# 將命名空間加入 API
api.add_namespace(test_get, '/test')

# 定義 RESTful 資源
@test_get.route("/hello/get4")
class HelloWorld(Resource):
    def get(self):
        return jsonify(data[3])
# 將命名空間加入 API
api.add_namespace(test_get, '/test')

# 定義 RESTful 資源
@test_get.route("/hello/get5")
class HelloWorld(Resource):
    def get(self):
        return jsonify(data[4])
# 將命名空間加入 API
api.add_namespace(test_get, '/test')



# 定義一個資源
@test_post.route('/post')
class HelloResource(Resource):
    @test_post.expect(input_model, validate=True)  # 使用模型定義預期的輸入
    def post(self):
        load = test_post.payload  # 自動解析並驗證請求數據
        name = load['name']
        for item in data['device']:
            if item['name'] == name:
                with open('data.json', 'r') as f:
                    file = json.load(f)
                    print('message: json:', file)
                return jsonify(item)
        if name == "all":
            return jsonify(data)
        return {'message': f'Hello, {name}!'}

# 將命名空間加入 API
api.add_namespace(test_post, '/test')

# 定義一個資源
@test_put.route('/put')
class HelloResource(Resource):
    @test_put.expect(input_model, validate=True)  # 使用模型定義預期的輸入
    def put(self):
        load = test_put.payload  # 自動解析並驗證請求數據
        name = load['name']
        for item in data['device']:
            if item['name'] == name:
                item['name'] = load['name']
                item['temp'] = load['temp']
                item['rh'] = load['rh']
                item['state'] = load['state']
                item['date_time'] = load['date_time']
                
                json_file = open(filename, 'w')
                json.dump(data, json_file)
                json_file.close()
                print(load)
                return jsonify(item)
        return {'error'}

# 將命名空間加入 API
api.add_namespace(test_put, '/test')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)