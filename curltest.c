#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char **argv){
	CURL *h;
	CURLcode res;
	char id[20], email[40],poststr[100];

	if(argc<3){
		printf("Usage: %s [ID] [email] \n",argv[0]);
		return 1;// means that program stops because user doesnt give enough info
	}
	sprintf(poststr,"ID=%s&email=%s",argv[1],argv[2]);//print mess into the screen
	curl_global_init(CURL_GLOBAL_ALL);
	h=curl_easy_init();
	if(h){
		curl_easy_setopt(h,CURLOPT_URL,"http://www.cc.puv.fi/~e1800930/curl.php");
		curl_easy_setopt(h,CURLOPT_POSTFIELDS, poststr);
		res = curl_easy_perform(h);
		if(res != CURLE_OK)
			printf("Error in curl_easy_perform().\n");
		else
			printf("Post data is sent.\n");
		curl_easy_cleanup(h);
	}
	curl_global_cleanup();
	return 0;
}
