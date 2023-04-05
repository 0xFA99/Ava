static const char user_agent[] = "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) QtWebEngine/5.15.2 Chrome/87.0.4280.144 Safari/537.36";
static const char search_engine_url[] = "https://www.google.com/";
static const char encode[] = "UTF-8";

static const char *answer_list[] = {
		// tracklist
		"//div[@class='title']",
		// richcast
		"//div[@class='JjtOHd']",
		// define
		"//div[@jsname='x3Eknd']",
		// list
		"//li[@class='TrT0Xe']",
		// pronounce
		"//div[@class='TQ7enb']",
		// weather
		"//span[@id='wob_tm']",
		// math
		"//span[@jsname='VssY5c']",
		// unit
		"//div[@class='IZ6rdc']",
		// currency
		"//input[@jsname='NotFQb']",
		// holiday
		"//div[@class='c7r50']",
		// basic
		"//div[@class='Z0LcW t2b5Cf']",
		// feat
		"//span[@class='hgKElc']",
		// quote
		"//div[@class='Qynugf']",
		// translate
		"//pre[@id='tw-target-text']",
		// lyric_us
		"//span[@jsname='YS01Ge']",
		// datetime
		"//div[@class='vk_bk dDoNo FzvWSb']",
		// know_right
		"//div[@jsname='g7W7Ed']/span"
};