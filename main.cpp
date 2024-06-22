#include <bits/stdc++.h>
void _1letters();
void _2letters();
void _3letters();
void findEmails(std::string unFiltered);
void append(std::string email);
std::string sendPostRequest(std::string letters);
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

std::vector<std::string> emails;


bool running = true;

void my_handler(int s){
        running = false;
}


int main(int argc, char* argv[]) {


    // struct sigaction sigIntHandler;

    // sigIntHandler.sa_handler = my_handler;
    // sigemptyset(&sigIntHandler.sa_mask);
    // sigIntHandler.sa_flags = 0;

    // sigaction(SIGINT, &sigIntHandler, NULL);


    auto start = std::chrono::high_resolution_clock::now();
    if(argc == 2){
        switch(atoi(argv[1])){
            case 1:
                _1letters();
                break;
            case 2:
                _2letters();
                break;
            case 3:
                _3letters();
                break;
            default:
                std::cout << "Incorrect usage.";
                return 1;
                break;
        }
    }else{
        std::cout << "Incorrect usage.";
        return 1;
    }


    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Execution time: " << std::setprecision(2) << (duration.count() / 60000000 ) << "m " << (duration.count() % 60000000) / 1000000.0 << "s\n";
    while(true){
        pause();
    }
    return 0;
}



std::string sendPostRequest(std::string letters){
    std::stringstream ss;
    ss << "curl --max-time 4 --retry 3 -s \'https://people-pa.clients6.google.com/$rpc/google.internal.people.v2.minimal.PeopleApiAutocompleteMinimalService/ListAutocompletions\'\
                        -H \'accept: */*\'\
                        -H \'accept-language: en-US,en;q=0.9\'\
                        -H \'authorization: SAPISIDHASH <redacted> \'\
                        -H \'content-type: application/json+protobuf\'\
                        -H \'cookie: <redacted> \'\
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
                        -H \'x-goog-api-key: <redacted> \'\
                        --data-raw \'[\"";
    ss << letters << "\",null,null,[\"GMAIL_COMPOSE_WEB_POPULOUS\"],8,null,null,null,[\"GMAIL_COMPOSE_WEB_POPULOUS\",null,2]]\'";

    std::string command = ss.str();
    std::string result = exec(command.c_str());
    return result;

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
void _1letters(){
    std::string letters = "";
    for(int i = 0; i < 26; i++){
        letters = "";
        letters += char(i + 'a');
        findEmails(sendPostRequest(letters));
    }
    return;
}



void _2letters(){
    std::string result = ""; 
    for(int i = 0; i < 676; i++){
        result = "";
        result += char((i / 26) + 'a');
        result += char((i % 26) + 'a');
        std::cout.flush();
        std::cout << result << "(" << i << "/" << 676 << ")" << "\r";
        findEmails(sendPostRequest(result));
    }

    return;
}
void _3letters(){
    std::string result = ""; 
    for(int i = 0; i < 17576; i++){
        result = "";
        result += char((i / 676) + 'a');
        result += char(((i / 26) % 26) + 'a');
        result += char((i % 26) + 'a');
        std::cout.flush();
        std::cout << result << "(" << i << "/" << 17576 << ")" << "\r";
        findEmails(sendPostRequest(result));
    }

    return;
}