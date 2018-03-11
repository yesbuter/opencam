# -*- coding: utf-8 -*-

#encoding=utf-8

import time
from weibo import APIClient

def get_access_token():
    print "getgetgetget"
    app_key = '2375582409'
    app_secret = '30efe65a663641a1c5b75f1f32063892'
    callback_url = 'https://api.weibo.com/oauth2/default.html'
    client = APIClient(app_key=app_key, app_secret=app_secret, redirect_uri=callback_url)
    # 获取授权页面网址
    auth_url = client.get_authorize_url()
    return auth_url
