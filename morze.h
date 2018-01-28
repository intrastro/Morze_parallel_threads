#include "lister.h"

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
