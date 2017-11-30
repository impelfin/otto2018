import os
import json
import jinja2
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin


def main():
    list_url = 'http://comic.naver.com/webtoon/weekday.nhn'
    html = requests.get(list_url).text
    soup = BeautifulSoup(html, 'html.parser')

    comic_list = []

    for a_tag in soup.select('a[href*=list.nhn]'):
        if not a_tag.select('.ico_updt'):
            continue

        img_tag = a_tag.find('img')
        url = urljoin(list_url, a_tag['href'])
        title = img_tag.attrs['title']
        img_src = img_tag['src']
        # img_data = requests.get(img_src, headers={'Referer': list_url}).content

        comic_list.append({
            'title': title,
            'url': url,
            'img': {
                'src': img_src,
                # 'data': img_data,
            },
        })

    res_path = os.environ['res']
    with open(res_path, 'wt', encoding='utf8') as f:
        # jinja2 템플릿 엔진을 통한 조합
        template_string = open('list.html', 'rt', encoding='utf8').read()
        template = jinja2.Template(template_string)
        html = template.render(comic_list=comic_list)

        # 응답 구조
        return_dict = {
            "status": 200,   # 응답의 Status Code
            "body": html,    # 응답 내용 (body)
            "headers": {     # 응답 헤더
                "Content-Type": "text/html"
            }
        }
        f.write(json.dumps(return_dict))


if __name__ == '__main__':
    main()
