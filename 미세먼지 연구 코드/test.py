import numpy as np
import json
import requests
from urllib import request
from urllib.parse import urlencode, quote_plus , unquote
import xml.etree.ElementTree as elemTree
import bs4
import pandas as pd
import sys,os
import time

col=['SchoolCode', 'address','Distance']
df = pd.DataFrame(columns = col)

csv_test= pd.read_csv("C:\\Users\\root\\Desktop\\미세먼지\\측정소정보.csv")

print(type(csv_test['측정소명'][0]))




key= "MY KEY is secret"
url = 'http://openapi.airkorea.or.kr/openapi/services/rest/ArpltnStatsSvc/getMsrstnAcctoLastDcsnDnsty'
decode_key = requests.utils.unquote(key)  # decode 해줍니다.

print("URL OK")

delta=1
for station_Name in csv_test['측정소명']:
    queryParams = '?' + urlencode({ 
        quote_plus('ServiceKey') : decode_key, 
        quote_plus('numOfRows') : '156' ,  #13*12 
        quote_plus('stationName') : station_Name , 
        quote_plus('searchCondition')  : 'MONTH'
        #quote_plus('msrstnName') : '동홍동' 
        })
    Request = requests.get(url + queryParams).text.encode('utf-8')
    info = bs4.BeautifulSoup(Request, 'html.parser')
    items =info.find("items")
    #tree =elemTree.fromstring(Request)
    #print("{}번째 {}".format(i,school_code),"\n")
    print("Request ok")
    print(station_Name)
    #print(info)
    print("\n\n\n")

    count =1
    year=['2006','2007','2008','2009','2010','2011','2012','2013','2014','2015','2016','2017','2018']
    month =['01','02','03','04','05','06','07','08','09','10','11','12']

    tmp=[' ' for i in range(13)]
    tmp[0] =station_Name
    data_year=year[0]
    
    for item in items.findAll("item"): 


        if data_year not in item.datatime.text:
            print(len(tmp) ,tmp) #debuger용

            # 칼럼 만들기
            month_col=['측정소명']
            for j in range(1,13):
                month_col.append(year[year.index(data_year)-1]+'-'+str(j))
            
            #데이터를 담을 공간
            df =pd.DataFrame([tuple(tmp)],columns=month_col)
            path =year[year.index(data_year)]+'.csv'

            if not os.path.exists(path):
                df.to_csv(year[year.index(data_year)]+'.csv',index='False',mode='w',encoding='utf-8-sig')
            else:
                df.to_csv(year[year.index(data_year)]+'.csv',index='False',mode='a',encoding='utf-8-sig', header=False)

            tmp=[' ' for i in range(13)]
            tmp[0] =station_Name


        data_year=year[0]

        #데이터를 찾아서 채우는 것
        for y in year:  #year먼저 찾고
            if y in item.datatime.text:
                data_year=y
                break
        
        for i, m in enumerate(month): #month를 다 탐색해서 관련 데이터 tmp에 담고 없으면 NULL 
            if data_year+"-"+m ==item.datatime.text: #datatime이 완전히 같으면
                if item.pm10avg.text !='none':  #그리고 pm10avg이 존재한다면~
                    tmp[i+1]=item.pm10avg.text


    print(len(tmp) ,tmp) #debuger용

    month_col=['측정소명']
    for j in range(1,13):
        month_col.append(year[year.index(data_year)-1]+'-'+str(j))
    df =pd.DataFrame([tuple(tmp)],columns=month_col)
    path =year[year.index(data_year)]+'.csv'
    if not os.path.exists(path):
        df.to_csv(year[year.index(data_year)]+'.csv',index='False',mode='w',encoding='utf-8-sig')
    else:
        df.to_csv(year[year.index(data_year)]+'.csv',index='False',mode='a',encoding='utf-8-sig', header=False)


    time.sleep(3)
    if delta % 10 ==0:
        break

    delta+=1
    
    
'''
for item in items.findAll("item"):
    tmp =pd.DataFrame([(school_code, item.addr.text, item.tm.text)],columns =col)
    df=df.append(tmp, ignore_index=True)
    #print(df)

print("{}번째".format(i))
path =os.path.join("C:\\Users\\root\\Desktop\\미세먼지", "res.csv")

df.to_csv(path,encoding='euc-kr', index=False, header =False)
'''

      
