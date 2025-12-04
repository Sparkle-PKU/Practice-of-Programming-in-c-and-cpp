import asyncio
from pyppeteer import launch
import re
import requests

async def get_html_from_detail_page(word):
    browser=await launch(
        headless=True,
        args=['--no-sandbox','--lang=zh-CN'],
        userDataDir='./tmp_profile')
    page=await browser.newPage()
    await page.setExtraHTTPHeaders({'Accept-Language':'zh-CN,zh;q=0.9'})
    url=f'https://cn.bing.com/dict/search?q={word}&cc=cn'
    await page.goto(url,{'waitUntil':'networkidle2'})
    await asyncio.sleep(1)
    content=await page.content()
    if 'id="synoid"' not in content:
        element=await page.querySelector('div.se_l>a')
        if element:
            await asyncio.gather(page.waitForNavigation({'waitUntil':'networkidle2'}),element.click())
            await asyncio.sleep(1)
            content=await page.content()
    await browser.close()
    return content

def extract_synonyms(html):
    match=re.search(r'<div id="synoid".*?</div>\s*</div>',html,re.S)
    if not match:
        return []
    block=match.group(0)
    synonyms=re.findall(r'<span class="p1-4 b_alink">(.*?)</span>',block)
    return list(set(synonyms))

def extract_image_url(html):
    match=re.search(r'<div class="img_area">.*?<img[^>]+src="([^"]+)"',html,re.S)
    if match:
        url = match.group(1)
        return "https://cn.bing.com"+url if url.startswith("/") else url
    return None

def download_image(url,word):
    try:
        res=requests.get(url,timeout=10)
        if res.status_code==200:
            with open(f"{word}.png","wb") as f:
                f.write(res.content)
    except Exception:
        pass

async def process_word(word,outfile):
    html=await get_html_from_detail_page(word)
    if not html:
        return
    synonyms=extract_synonyms(html)
    if synonyms:
        outfile.write(f"${word}\n")
        for syn in synonyms:
            outfile.write(f"{syn}\n")
    img_url=extract_image_url(html)
    if img_url:
        download_image(img_url,word)

async def main():
    with open("words.txt","r",encoding="utf-8") as f:
        words=[w.strip() for w in f if w.strip()]
    with open("result.txt","w",encoding="utf-8") as out:
        for word in words:
            await process_word(word,out)

if __name__=="__main__":
    try:
        asyncio.run(main())
    except RuntimeError:
        pass
