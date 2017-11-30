
## Azure Function을 활용해서, 네이버 웹툰 웹데이트 현황 크롤링해서 HTML로 보여주기

+ 새 함수 앱
    - Http Trigger/Output으로 생성
    - 권한수준은 Anonymous로 지정
+ 생성된 함수앱의 통합 메뉴
    - 선택한 HTTP 메서드에 **GET**추가

동작 페이지 : https://snu2017.azurewebsites.net/api/HttpTriggerPython31

### 실행에 앞서

파이썬 3 설치 및 라이브러리 설치가 필요합니다. 함수 앱 > 플랫폼 기능 > 고급도구 (KUDU) > Debug Console > CMD 에서 아래 명령을 하나씩 실행주세요.

```
# Python 3.6 설치
쉘> nuget.exe install -Source https://www.siteextensions.net/api/v2/ -OutputDirectory D:\home\site\tools python361x64

# Azure Function에서 접근가능한 경로에 Python 명령 복사
쉘> mv /d/home/site/tools/python361x64.3.6.1.3/content/python361x64/* /d/home/site/tools/

# 파이썬 팩키지 설치
쉘> d:/home/site/tools/python -m pip install requests beautifulsoup4 jinja2
```

---

[AskDjango 페이스북 그룹](https://fb.com/groups/askdjango)
