import urllib.request
import urllib.error
import re
import urllib
import socket
import math

class bloom:
    'bloom filter'
    def __init__(self,n,x):
        self.arr = []  # bloom filter bit array
        self.n=n
        self.x=x
        self.m=int(math.ceil(1.44*n*math.log(1/x,2)))       #size of bit array
        self.k=int(math.ceil(math.log(2)*1.44*math.log(1/x,2)))  #number of hash func

        for x in range(self.m):
            self.arr.append(0)
        self.BKDRseed = [31, 131, 1313, 13131, 131313, 1313131, 13131313, 131313131, 1313131313, 13131313131]  # hash seed

    def BKDRhash(self,str, seed_index):
        # BKDR，根据传入的种子使用对应哈希函数计算，seed range(0-9)
        num = 0
        for i in range(len(str)):
            num = num * self.BKDRseed[seed_index] + ord(str[i])
        return num

    def check(self,str):
        for i in range(self.k):
            bit_index = self.BKDRhash(str, i) % self.m
            if self.arr[bit_index] == 0:
                return 0  #未访问
        return 1          #认为已访问

    def add(self,str):
        for i in range(self.k):
            bit_index = self.BKDRhash(str, i) % self.m
            self.arr[bit_index] = 1


class crawler:
    '爬虫'

    def __init__(self,begin_path,least_page,least_img):

        self.least_img=least_img
        self.least_page=least_page
        self.page_code = ''  # 当前网页的源代码
        self.img_number = 1  # 记录当前已获取图片
        self.url_number = 1
        self.suffix_arr = ['.jpg', '.jpeg', '.png', '.gif', '.bmp']  # 支持的图片格式
        self.url_stack = ['']  # 用于存放待访问的链接的栈
        self.url_stack.append(begin_path)
        self.filter=bloom(1000,0.001)



    def start(self):
        while self.url_number < 1200 or self.img_number < 11000:
            if len(self.url_stack) == 0:
                print('URL STACK EMPTY')
                break
            url = self.url_stack.pop()
            if self.filter.check(url) == 1:
                continue
            self.filter.add(url)
            print('-----开始访问第' + str(self.url_number) + '个网页,队列中还有' + str(len(self.url_stack)) + '个:' + url)
            self.url_number += 1
            if self.get_page_code(url) == 0:
                self.save_url_in_page()
                self.save_page_img()

    def get_page_code(self,url):
        # input:网页链接
        # output:该网页的源代码
        try:
            request = urllib.request.Request(url)
            request.add_header("User-Agent", "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)")
            response = urllib.request.urlopen(request, timeout=10)
        except urllib.error.HTTPError as e:
            print('【HTTP ERROR】')
            return -1
        except urllib.error.URLError as e:
            print('【URL ERROR】')
            return -1
        except socket.timeout as e:
            print('【TIMEOUT ERROR】')
            return -1
        except Exception as e:
            print('【Unknown ERROR】')
            return -1
        else:
            self.page_code = response.read().decode("utf-8")  # 获取网页源代码
            return 0

    def save_page_img(self):
        # input： 某一网页的源代码
        # do: 下载该网页上显示的所有相关图片

        # 正则表达式获取所有图片链接，保存在数组中
        img_pattern = re.compile('data-original="(.*?)"')
        img_urls = img_pattern.findall(self.page_code)

        for link in img_urls:
            # 解析图片后缀
            suffix = 'INIT'
            for i in self.suffix_arr:
                if i in link:
                    suffix = i
                    break
            if suffix == 'INIT':
                print('ERROR WHEN GET SUFFIX')
                return
            try:
                # 下载
                urllib.request.urlretrieve(link, 'd://ithome_2//' + str(self.img_number) + suffix)
            except urllib.error.HTTPError as e:
                print('【HTTP ERROR】')
            except urllib.error.URLError as e:
                print('【URL ERROR】')
            except Exception as e:
                print('【Unknown ERROR】')
            else:
                print('获得第' + str(self.img_number) + '张照片: ' + link)
                self.img_number += 1

    def save_url_in_page(self):
        # input：某一网页的源代码
        # do：把该网页上的所有网站链接存放到栈中
        htm_pattern = re.compile('href="(.*?)"')  # 页面链接的正则表达式匹配规则
        all_url = htm_pattern.findall(self.page_code)  # 使用正则表达式获取源代码中的所有链接，存为数组
        for i in all_url:
            if 'https://www.ithome.com' in i:
                if '.htm' in i:
                    self.url_stack.append(i)


cra=crawler('https://www.ithome.com/html/android/341588.htm',1000,10000)
cra.start()