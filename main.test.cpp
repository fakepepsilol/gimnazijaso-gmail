#include<bits/stdc++.h>


void append(std::string email);
void _1letters(std::string startString);
void findEmails(std::string unFiltered);
std::string sendPostRequest(std::string letters);
std::string exec(const char* cmd);

std::vector<std::string> emails;


int main(int argc, char* argv[]){
    std::freopen("mails.txt", "r", stdin);
    
    std::string temp = "";
    while(std::getline(std::cin, temp)){
        emails.push_back(temp);
    }
    fclose(stdin);
    // reading the fucking 1080 line file
    int initialSize = emails.size();




    int diffs = 1;
    int counter = 1;
    for(int i = 1; i < emails.size(); i++){ // finds the repetitions :333333
        if(emails[i].substr(0, 3) == emails[i-1].substr(0, 3)){
            counter++;
        }else{
            std::cout << emails[i-1].substr(0, 3) << " repeats " << counter << " times. <--" << emails[i-1] << "(" << diffs << "/455)\n";
            _1letters(emails[i-1].substr(0,3));
            diffs++;
            counter = 1;
        }
    }
    std::cout << diffs;
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("");
    std::puts("the emails that need to be added manually:");

    for(int i = initialSize; i < emails.size(); i++){
        std::cout << emails[i] << "\n";
    }



    return 0;
}




void _1letters(std::string startString){
    std::string letters = "";
    for(int i = 0; i < 26; i++){
        letters = startString;
        letters += char(i + 'a');
        findEmails(sendPostRequest(letters));
    }
    return;
}








void append(std::string email){
    if(email.substr((email.length() - std::string("@gimnazijaso.edu.rs").length()), email.length()) != "@gimnazijaso.edu.rs"){
        //std::cout << "not gimnazijaso.edu.rs: " << email << "\n";
        return;
    }
    if(emails.size() == 0){
        std::cout << email << "\n";
        emails.push_back(email);
    }else{
        for(std::string emailInArray : emails){
            if(emailInArray == email){
                return;
            }
        }
        emails.push_back(email);
        std::cout << email << "\n";
    }
}

void findEmails(std::string unFiltered){
    bool foundOne = false;
    std::string email = "";
    for(int i = 0; i < unFiltered.length(); i++){
        foundOne = false;
        if(unFiltered[i] == '@'){
            for(int j = i; j > 0; j--){
                if(unFiltered[j] == '"'){
                    for(int k = j+1; k < unFiltered.length(); k++){
                        if(unFiltered[k] == '"'){
                            foundOne = true;
                            append(email);
                            email = "";
                            break;
                        }else{
                            email += unFiltered[k];
                        }
                    }
                }
                if(foundOne){
                    break;
                }
            }
        }
    }

    return;
}

std::string sendPostRequest(std::string letters){
    std::stringstream ss;
    ss << "curl --max-time 4 --retry 3 -s \'https://people-pa.clients6.google.com/$rpc/google.internal.people.v2.minimal.PeopleApiAutocompleteMinimalService/ListAutocompletions\'\
                        -H \'accept: */*\'\
                        -H \'accept-language: en-US,en;q=0.9\'\
                        -H \'authorization: SAPISIDHASH 1714297009_e15118cf3d545773ce73c46007a48149e813aa17\'\
                        -H \'content-type: application/json+protobuf\'\
                        -H \'cookie: SID=g.a000jAgQSN5JPp45mXpkDbrYO6_3FaZqf-QxLFB5me1NeWaAA8zstdQT1IdfjmZd9xKXLAbJ9AACgYKAcoSAQASFQHGX2Mi3Nb1P7hXJc5rVseonYqnuRoVAUF8yKqEB8ujLOAvJ2GEv904v71v0076; __Secure-1PSID=g.a000jAgQSN5JPp45mXpkDbrYO6_3FaZqf-QxLFB5me1NeWaAA8zsGc-OBWitjZwnS7B66VAhVgACgYKAf0SAQASFQHGX2Mi_MHWvECDtyAK-w50d80H_RoVAUF8yKoTqgg3sEz7B7nu4gGcSbvz0076; __Secure-3PSID=g.a000jAgQSN5JPp45mXpkDbrYO6_3FaZqf-QxLFB5me1NeWaAA8zsKPIip_tGnq9RAfLsjgvdHQACgYKAcgSAQASFQHGX2MiImTOubG6hzvv5s3RIgsFPxoVAUF8yKpa4bMWxEE0Fh1DOE0QvBpV0076; HSID=ASb3LRs0LuTqCSdqD; SSID=AzsIQSnUQKWG6IyE_; APISID=VSdKseTlxTEWqpcY/AE7V55xkiS1ln9Grg; SAPISID=Ol4dLCPT4qBzhcBk/AaxcuXaZdZYoVippw; __Secure-1PAPISID=Ol4dLCPT4qBzhcBk/AaxcuXaZdZYoVippw; __Secure-3PAPISID=Ol4dLCPT4qBzhcBk/AaxcuXaZdZYoVippw; NID=513=OoAod9F8QJ-Ra3uU0DO_C__mwP9T7LInVgP_jUfrPPRrVUekXw21gjffzMGK3TMOAyZN0KB9TQjMJpUO2aFfH7uU05k4Kh64VqtdcJDxUMKru0t0rWlrHM8An-UdE8g4aGlqsTseUWoXb7OVu-QThwzpNJVRuTs4ohbKzvLTxUZR1s27FTIsoGpPy07-tz7dpMytqt0Sv-mwFhGyso0hD3rbCen54JIvjRuTkeoZjMAckvrzza8JUakl4PU2qWG7BZ4; __Secure-1PSIDTS=sidts-CjIBLwcBXI4fWZTmuNbnL7Dz3jOMTCK9bfiqQxx9lmFTlfFz412-Xq1tBXb11XCDthI1zRAA; __Secure-3PSIDTS=sidts-CjIBLwcBXI4fWZTmuNbnL7Dz3jOMTCK9bfiqQxx9lmFTlfFz412-Xq1tBXb11XCDthI1zRAA; SIDCC=AKEyXzVFvub0THT5Ox9NdISDczk4RHZ-_bzT5uw8Q5isFWOlukN_IKQQ6v28czOrPZ19u5cw_g; __Secure-1PSIDCC=AKEyXzVHoMmjoZD0bsJYdYzxWJTWsqxEjaWfRQDFtuTYdgFYrqElzGKsTKxKRVwDVxnfxSJlln0; __Secure-3PSIDCC=AKEyXzX8FY9ZiE9V0p5pjrCE8ghSwF7LsHq3RKHNxMWv_ANuSDbQywrn75Y_hXeO97mYazOwDw\'\
                        -H \'origin: https://mail.google.com\'\
                        -H \'priority: u=1, i\'\
                        -H \'referer: https://mail.google.com/\'\
                        -H \'sec-ch-ua: \"Chromium\";v=\"123\", \"Not:A-Brand\";v=\"8\"\'\
                        -H \'sec-ch-ua-arch: \"\"\'\
                        -H \'sec-ch-ua-bitness: \"\"\'\
                        -H \'sec-ch-ua-full-version: \"\"\'\
                        -H \'sec-ch-ua-full-version-list;\'\
                        -H \'sec-ch-ua-mobile: ?0\'\
                        -H \'sec-ch-ua-model: \"\"\'\
                        -H \'sec-ch-ua-platform: \"Linux\"\'\
                        -H \'sec-ch-ua-platform-version: \"\"\'\
                        -H \'sec-ch-ua-wow64: ?0\'\
                        -H \'sec-fetch-dest: empty\'\
                        -H \'sec-fetch-mode: cors\'\
                        -H \'sec-fetch-site: same-site\'\
                        -H \'user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/123.0.6312.122 Safari/537.36\'\
                        -H \'x-client-data: CI2OywE=\'\
                        -H \'x-goog-api-key: AIzaSyBm7aDMG9actsWSlx-MvrYsepwdnLgz69I\'\
                        --data-raw \'[\"";
    ss << letters << "\",null,null,[\"GMAIL_COMPOSE_WEB_POPULOUS\"],8,null,null,null,[\"GMAIL_COMPOSE_WEB_POPULOUS\",null,2]]\'";

    std::string command = ss.str();
    std::string result = exec(command.c_str());
    return result;

}

std::string exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}