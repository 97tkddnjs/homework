import folium
import webbrowser
import psycopg2
import sys
import os
from urllib.request import urlopen

import pandas as pd
import numbers
import math

import urllib.request , bs4

import json
import requests

from xml.etree.ElementTree import parse
from urllib.parse import urlencode, quote_plus


from django.shortcuts import render
from django.views import generic
# Create your views here.
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt


from .models import district_info
from .models import school_info
from .forms import TodoForm


@csrf_exempt
def index(request):
    conn_string = "host='localhost' dbname ='postgres' user='postgres' password='9407740'"
    conn = psycopg2.connect(conn_string)
    cur = conn.cursor()
    selected_city = ""
    selected_district = ""
    district_list = ""
    city_list = ""
    school_name = ""
    find_school_name = ""
    find_school = ""
    school_type = ""
    #버튼누른경우
    if request.method == "POST":
        #city 와 district 값이 모두 선택 되어 전달 된 경우
        selected_city = request.POST['select_city']
        selected_district = request.POST['select_district']
        school_type = request.POST['select_school_type']
        
        if(school_type == "초등학교"):
            school_type = 2
        elif(school_type == "중학교"):
            school_type = 3
        elif(school_type == "고등학교"):
            school_type = 4
        else:
            school_type = 5
        if selected_district != "도시선택" :
            selected_city = request.POST['select_city']
            selected_district = request.POST['select_district']
            sql = "select id, name, ofice_name ,road_addr, addr from school_info where road_addr like '%"
            sql += selected_city
            sql += "%' and road_addr like '%"
            sql += selected_district
            sql += "%' and type = '"
            sql += str(school_type)
            sql += "';"
            cur.execute(sql)
            find_school = cur.fetchall()

            
            selected_city = request.POST['select_city']
            sql = "select district from district_info where city = '"
            sql +=  selected_city
            sql += "';"
            cur.execute(sql)
            district_list = cur.fetchall()
            

        #city만선택되고버튼눌러district값넣어야하는경우
        elif selected_district == "도시선택":
            selected_city = request.POST['select_city']
            sql = "select district from district_info where city = '"
            sql +=  selected_city
            sql += "';"
            cur.execute(sql)
            district_list = cur.fetchall()
        else :
            district_list = [("에러")]


    sql = "select distinct city from district_info"
    cur.execute(sql)
    city_list = cur.fetchall()
    
    sql = "select distinct city from district_info"
    cur.execute(sql) 
    city_list = cur.fetchall()

    
    
    conn.close()

    context = {
            'city_list' : city_list,
            'district_list' : district_list,
            'selected_city' : selected_city,
            'selected_district' : selected_district,
            'find_school' : find_school,
            'find_school_name' : find_school_name,
            'school_name'  : school_name,
            }
    return render(request, 'index.html', context) 

@csrf_exempt
def name(request):
    if request.method== "POST":
        selected_city = ""
        selected_district = ""
        district_list = ""
        city_list = ""
        find_school = ""
        school_name = request.POST['school_name']
        conn_string = "host='localhost' dbname ='postgres' user='postgres' password='9407740'"
        conn = psycopg2.connect(conn_string)
        cur = conn.cursor()

        sql = "select id, name, ofice_name ,road_addr, addr from school_info where name like '%"
        sql += school_name
        sql += "%';"
        cur.execute(sql)
        find_school_name = cur.fetchall()

        sql = "select id, addr from school_info where name like '%"
        sql += school_name
        sql += "%';"
        cur.execute(sql)
        school_url = cur.fetchall()

        sql = "select distinct city from district_info"
        cur.execute(sql)
        city_list = cur.fetchall()
        conn.close()
        
        context = {
                'city_list' : city_list,
                'district_list' : district_list,
                'selected_city' : selected_city,
                'selected_district' : selected_district,
                'find_school' : find_school,
                'find_school_name' : find_school_name,
                'school_name'  : school_name,
                'school_url': school_url,
                }
    return render(request,'index.html',context)

@csrf_exempt
def show_map(request):
    info = "null"
    if request.method== "GET" and request.GET.copy():
        info = request.GET.copy()
        for i in info:
            ID = str(i)[2:-2]

        conn_string = "host='localhost' dbname ='postgres' user='postgres' password='9407740'"
        conn = psycopg2.connect(conn_string)
        cur = conn.cursor()

        sql = "select latitude from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        latitude = str(cur.fetchall())[3 :-4]
        
        sql = "select longitude from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        longitude = str(cur.fetchall())[3 :-4]
        
        sql = "select name from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        name = str(cur.fetchall())[3 :-4]
        
        
        conn.close()
        
        Map= folium.Map(location=[latitude, longitude], tiles = "OpenStreetMap", zoom_start=20)
        folium.Marker(location = [latitude, longitude], icon = folium.Icon(color='blue', icon = 'star', popup = name)).add_to(Map)
        Map_dir = 'C:/Users/Hoon/Desktop/django/web/apps/templates/map.html'
        Map.save(Map_dir)

#    return HttpResponse(name)
    return render(request,'map.html')

@csrf_exempt
def show_detail(request):
    info = ""
    info2 = ""
    info3 = ""
    name = ""
    # pmdata = []
    if request.method== "GET" and request.GET.copy():
        info = request.GET.copy()
        for i in info:
            ID = str(i)[2:-2]

        conn_string = "host='localhost' dbname ='postgres' user='postgres' password='9407740'"
        conn = psycopg2.connect(conn_string)
        cur = conn.cursor()

        sql = "select name from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        name = cur.fetchall()
        name = str(name)[3:-4]
        
        
        sql = "select id, name, type, public, branch from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        info = cur.fetchall()
        
        
        sql = "select state, addr, support_name, office_code, ofice_name from school_info  where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        info2 = cur.fetchall()
        
        sql = "select support_code,road_addr , latitude, longitude from school_info where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        info3 = cur.fetchall()
        
        
        sql = "select tm_x, tm_y from school_tm where id = '"
        sql += ID
        sql += "';"
        cur.execute(sql)
        school_tm = cur.fetchall()

        school_tmX = school_tm[0][0]
        school_tmY = school_tm[0][1]

        url = 'http://openapi.airkorea.or.kr/openapi/services/rest/MsrstnInfoInqireSvc/getNearbyMsrstnList'
        key = "영업비밀~~"
        key = requests.utils.unquote(key)
        
        queryParams = '?' + urlencode({ 
            quote_plus('ServiceKey') : key, 
            quote_plus('tmX') : school_tmX, 
            quote_plus('tmY') : school_tmY 
            })

        try:
            request_api = requests.get(url + queryParams).text.encode('utf-8')
            station_info = bs4.BeautifulSoup(request_api, 'lxml-xml')
    
            station_name = station_info.find("stationName")
            station_name = station_name.text
            tm_dis = station_info.find("tm")
            tm_dis = tm_dis.text
    
            
            url = 'http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty'
            queryParams = '?' + urlencode({ 
                quote_plus('ServiceKey') : key,
                quote_plus('numOfRows') : '30', 
                quote_plus('pageNo') : '1', 
                quote_plus('stationName') : station_name, 
                quote_plus('dataTerm') : 'MONTH', 
                quote_plus('ver') : '1.2' 
            })
    
            request_api = requests.get(url + queryParams).text.encode('utf-8')
            air_info = bs4.BeautifulSoup(request_api, 'lxml-xml')
        except:
            request_api = requests.get(url + queryParams).text.encode('utf-8')
            station_info = bs4.BeautifulSoup(request_api, 'lxml-xml')
    
            station_name = station_info.find("stationName")
            station_name = station_name.text
    
            tm_dis = station_info.find("tm")
            tm_dis = tm_dis.text
            
            url = 'http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty'
            queryParams = '?' + urlencode({ 
                quote_plus('ServiceKey') : key,
                quote_plus('numOfRows') : '30', 
                quote_plus('pageNo') : '1', 
                quote_plus('stationName') : station_name, 
                quote_plus('dataTerm') : 'MONTH', 
                quote_plus('ver') : '1.2' 
            })
    
            request_api = requests.get(url + queryParams).text.encode('utf-8')
            air_info = bs4.BeautifulSoup(request_api, 'lxml-xml')

        time = air_info.find_all("dataTime")
        pm10 = air_info.find_all("pm10Value")
        pm10_24 = air_info.find_all("pm10Value24")
        pm25 = air_info.find_all("pm25Value")
        pm25_24 = air_info.find_all("pm25Value24")
        pmdata = []
        a = 0

        for i,j,k,x,y in zip(time, pm10, pm10_24, pm25, pm25_24):

            pmdata.append([])
            pmdata[a].append((i.text, j.text, k.text, x.text, y.text))
            a += 1

        
        conn.close()  
        
    context = {
            'detail_info' : info,
            'detail_info2' : info2,
            'detail_info3' : info3,
            'dis':tm_dis,
            'pmdata' : pmdata,          
            'name' : name
            }

    return render(request,'detail.html', context)

