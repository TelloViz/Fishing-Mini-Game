#pragma once


#include <string>
          class Singleton {
          public:
               // This is how clients can access the single instance
               static Singleton* getInstance();

               void setId(std::string id) { id_ = id; }
               std::string getId() { return(id_); }

          protected:
               std::string id_;

          private:
               static Singleton* inst_;   // The one, single instance
               Singleton() : id_("") {} // private constructor
               Singleton(const Singleton&);
               Singleton& operator=(const Singleton&);
          };

          // Define the static Singleton pointer
          Singleton* Singleton::inst_ = NULL;

          Singleton* Singleton::getInstance() {
               if (inst_ == NULL) {
                    inst_ = new Singleton();
               }
               return(inst_);
          }

          // USAGE:: 
          //int main() {

          //     Singleton* p1 = Singleton::getInstance();

          //     p1->setValue(10);

          //     Singleton* p2 = Singleton::getInstance();

          //     cout << "Value = " << p2->getValue() << '\n';
          //}
     //};
