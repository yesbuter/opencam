# -*- coding: utf-8 -*-

#encoding=utf-8

import time
from weibo import APIClient
def upload_pic(code):
    #print "codecodecodecode"
    #print code
    app_key = '2375582409'
    app_secret = '30efe65a663641a1c5b75f1f32063892'  
    callback_url = 'https://api.weibo.com/oauth2/default.html'  
    client = APIClient(app_key=app_key, app_secret=app_secret, redirect_uri=callback_url)  
    #code = raw_input("Input code:")
    r = client.request_access_token(code)
    access_token = r.access_token
    expires_in = r.expires_in

    client.set_access_token(access_token, expires_in)  
      
    idx = 1  
    default_msg_part_1 = 'This is no.'  
    default_msg_part_2 = ' msg sent automatically from benny"s robot HAHAHA'  
   
    # send a weibo with img  
    f = open('test.jpg', 'rb')
    #r = client.statuses.share.post(status=u'test: weibo with an img. -benny')
    r = client.statuses.share.post(access_token = access_token, status=u'测试 http://www.weibo.com/', pic=f)
    f.close() # APIClient不会自动关闭文件，需要手动关闭
    #return access_token
