#include <iostream>
#include <thread>
#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <mutex>
using namespace std;

struct letter
    {
    int symbol;
    letter* link_front;
    letter* link_back;
    };
typedef letter *Pletter;

template <typename new_type> class lister
    {
    private:
        Pletter link_back;
        Pletter link_front;

    public:
        std::mutex locker;

        lister ()
            {
            link_back = new letter;
            link_front = new letter;

            link_back -> link_back = nullptr;
            link_back -> link_front = link_front;
            link_front -> link_back = link_back;
            link_front -> link_front = nullptr;

            std::cout << "created" << std::endl;
            }

        ~lister ()
            {
            std::cout << "deleted" << std::endl;
            }

        bool push_Back (new_type value)
            {
            std::cout << "puB_try" << std::endl;

            locker.lock ();

            Pletter link_tmp = new letter;

            link_back -> link_back = link_tmp;

            link_tmp -> link_back = nullptr;

            link_tmp -> link_front = link_back;

            link_back = link_tmp;

            link_back -> symbol = (int)value;

            delete link_tmp;

            locker.unlock ();

            return true;
            }

        bool push_Front (new_type value)
            {
            std::cout << "puF_try" << std::endl;

            locker.lock ();

            Pletter link_tmp = new letter;

            link_front -> link_front = link_tmp;

            link_tmp -> link_front = nullptr;

            link_tmp -> link_back = link_front;

            //link_front = link_front -> link_front;

            link_front = link_tmp;

            link_front -> symbol = (int)value;

            delete link_tmp;

            locker.unlock ();

            return true;
            }

        bool pop_Back ()
            {
            std::cout << "poB_try" << std::endl;

            locker.lock ();

            if (link_back -> link_front != link_front)
                {
                Pletter link_tmp = link_back;

                link_back -> link_front -> link_back = nullptr;

                link_back = link_back -> link_front;

                delete link_tmp;

                locker.unlock ();

                return true;
                }
            else
                {
                std::cout << "pop_back_false";

                locker.unlock ();

                return false;
                }
            }

        bool pop_Front ()
            {
            std::cout << "poF_try" << std::endl;

            locker.lock ();

            if (link_back -> link_front != link_front)
                {
                Pletter link_tmp = link_front;

                link_front -> link_back -> link_front = nullptr;

                link_front = link_front -> link_back;

                delete link_tmp;

                locker.unlock ();

                return true;
                }
            else
                {
                locker.unlock ();

                return false;
                }
            }

        int ret_Back ()
            {
            std::cout << "rB_try" << std::endl;

            return (int) link_back -> symbol;
            }

        int ret_Front ()
            {
            std::cout << "rf_try" << std::endl;

            return (int) link_front -> symbol;
            }

        bool check_end ()
            {
            if (link_back -> link_front == link_front)
                {
                //std::cout << "true";

                return true;
                }
            else
                {
                //std::cout << "false";

                return false;
                }
            }
    };

class morze
    {
    public:

        std::mutex locker;

        lister <int> new_list;

        morze ()
            {
            std::cout << "morze creation" << std::endl;

            Beep (600, 1500);

            start_morze ();
            }

        ~morze ()
            {
            }

        void start_morze ()
            {
            auto writing = std::thread ([this] {this -> writing (std::ref (new_list));});

            writing.detach ();

            auto beeping = std::thread ([this] {this -> beeping (std::ref (new_list));});

            beeping.detach ();
            }


        void writing (lister <int> &new_list)
            {
            char symbol = '\0';

            while (1)
                {
                symbol = getch ();

                std::cout << "OK_getting" << std::endl;

                locker.lock ();

                if (new_list.push_Front (symbol))
                    {
                    std::cout << "OK_writing" << std::endl;
                    }

                locker.unlock ();
                }
            }

         void beeping (lister <int> &new_list)
            {
            Sleep (10000);

            std::cout << "!!!" << std::endl;

            while (1)
                {
                locker.lock ();

                if (new_list.check_end () == FALSE)
                    {
                    Beep (700 + new_list.ret_Back (), 200);

                    if (new_list.pop_Back ())
                        {
                        std::cout << "OK_beep" << std::endl;
                        }

                    Sleep (2000);
                    }

                locker.unlock ();
                }
            }
    };

int main ()
    {
    std::cout << "main began" << std::endl;

    morze Head_morze;

    //Beep (600, 1500);

    Sleep (100000);

    std::cout << "main ended" << std::endl;
    }
