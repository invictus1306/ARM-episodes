#include <iostream>
#include <cerrno>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#define PORT     4444
#define MAX_NUM  10

using namespace std;

int fd_sock;
static int roulette;

class Note{
  protected:
    unsigned int note_number;
    string note_desc[10];

  public:
    void insert_note(string ins_note){
      if (note_number<10){
        note_desc[note_number] = ins_note;
        cout << "Note added!" << endl;
        note_number++;
      }else{
        cout << "You can not add more notesd!" << endl;
      }
    }

    void delete_note(){
      if(note_number>0){
        note_number--;
      }else{
        note_number=0;
      }

      if (!note_desc[note_number].empty()){
        note_desc[note_number].clear();
        cout << "Note deleted!" << endl;
      }else{
        cout << "No note to delete!" << endl;
      }
    }

    int edit_note(unsigned int new_index, string new_note){
      if((new_index<10)&&(!note_desc[new_index].empty())){
        note_desc[new_index] = new_note;
        cout << "Note modified!" << endl;
      }else{
        cout << "You can not edit this note" << endl;
      }
      return 0;   
    }

    virtual int show_all_notes(){
      return 0;
    }
};

class Edit : public Note{
  public:
    virtual int show_all_notes(){
      unsigned int i;
      for(i=0;i<note_number;i++){
        cout << note_desc[i] << endl;
      }
      return 0;
    }
};

void stack_pivot(){
  asm volatile(
    "ldr sp,[r4, #0x0c] \n\t"
    "ldr sp, [sp] \n\t"      
    "pop {lr, pc} \n\t"
  );
}

void set_address(){
  int *num = new int[12]; 
  int tmp;
  cout << "Enter the number" << endl;
  cin >> tmp;
  num[0]=tmp;
  cout << "Number correctly inserted" << endl;
}

void stack_info(){
  string str;
  printf("Debug informations area \n");
  cin >> str;
  printf(str.c_str());
}

int note(){
  int client_sockfd;
  struct sockaddr_in caddr;
  socklen_t acclen = sizeof(caddr);
  unsigned int index = 0;
  unsigned int index_to_edit=0;
  string new_note;
  string edit_not;
  int res, i;
  char c, ch;
  char *tmp;
  string input;
  char wel_msg[512] = "Welcome! Enjoy to use this app to manage your notes";
  
  acclen = sizeof(caddr);

  Edit *edit_obj = new Edit;

  while(1){
    if((client_sockfd = accept(fd_sock, (struct sockaddr *) &caddr, &acclen)) < 0 ){
      std::cerr << strerror(errno) << std::endl;
      exit(1);
    }

    dup2(client_sockfd, 0);
    dup2(client_sockfd, 1);
    dup2(client_sockfd, 2);
    
    cout << wel_msg << endl;

    while(1){
      cout << "1- Insert a note" << endl;
      cout << "2- show all notes" << endl;
      cout << "3- Edit a note" << endl;
      cout << "4- Delete the last note" << endl;
      cout << "5- Set your address :)" << endl;
      cout << "0- Change the message" << endl;
      cout << endl;

      std::cin.clear();
      cin >> input;
      c = input[0];
      index = atoi(&c);

      switch(index){
        case 1:
          cout << "Enter the new value: " << endl;
          cin >> new_note;
          edit_obj->insert_note(new_note);
          break;
        
        case 2:
          edit_obj->show_all_notes();
          break;

        case 3:
          cout << "Insert the index of the note to modify: " << endl;
          cin >> input;
          c = input[0];
          index_to_edit = atoi(&c);
          cout << "Enter the new value: " << endl;
          cin >> edit_not;
          res = edit_obj->edit_note(index_to_edit, edit_not);
          break;

        case 4:
          edit_obj->delete_note();
          cout << "Try to set the roulette number: " << endl;
          cin >> roulette;
          delete edit_obj;
          break;
 
        case 5:
          set_address();
          break;
        
        case 0:
          cout << "Enter the new message: " << endl;
          tmp = wel_msg;
          i=0;
          ch = std::cin.get();
          while ((ch = std::cin.get()) != 51 && i<256){
            memcpy(tmp, &ch, 256);
            tmp = tmp + 1;
            i += 1;
          }
          break;
        
        case 9:
          stack_info();
          cout << "Debug informations" << endl;
          cout << "Address of wel_msg" << "---" << &wel_msg << endl;
          cout << "Address of roulette" << "---" << &roulette << endl;
          cout << "Well done!" << endl;
          break;

        default:
          cout << "Please select a correct option! " << endl;
          break;
      }
    }
  }
  close(client_sockfd);
  return 0;
}

int main(){
  pid_t pid;
  int var = 1;
  struct sockaddr_in sockaddr;

  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr.sin_port = htons(PORT);

  while(1){
    pid = fork();
    if ( pid == 0 ){
      cout << "Run pid=" << getpid() << endl;
      if ((fd_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(1);
      }

      if(setsockopt(fd_sock, SOL_SOCKET, SO_REUSEADDR, &var, sizeof(int)) <0) {
       std::cerr << strerror(errno) << std::endl;
       exit(1);
      }

      if (bind(fd_sock, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) <0 ){
        std::cerr << strerror(errno) << std::endl;
        exit(1);
      }
      
      if (listen(fd_sock, MAX_NUM) < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(1);
      }
      
      note();
    
    }
    else{
        wait(NULL);
        close(fd_sock);
    }
  }   
  return 0;
}

