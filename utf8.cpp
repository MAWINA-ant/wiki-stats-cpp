#include "utf8.hpp"

std::wstring utf8_to_utf16 (std::string str){
    uint8_t first_byte, addition_byte;
    std::wstring result = L"";          // строка с результатом работы функции
    int i = 0;
    while (i < str.length()){           // Пока не пройдём все символы
        first_byte = str[i];            // Запоминаем первый байт текущего символа
        result.push_back(first_byte);   // и помещаем в строку результата

        if (first_byte & 0x80){         // если кодировка символа занимает больше одного байта,
            first_byte = first_byte << 1;// то удалем первую единицу сдвигом
        }

        uint32_t cl_int = 0x3F;         // маска для "затирания" начальные единицы
        while (first_byte & 0x80){      // пока не удалим все начальные единицы в 'first_byte'
            addition_byte = str[++i];   // Считываем очередной байт кодировки
            
            // Изменяем последний символ строки с результатом
            int last = result.length()-1;
            // затираем первую единицу и дописывем 6 последних бит дополнительного байта
            result[last] = ((result[last] & cl_int) << 6 ) | (addition_byte & 0x3F);

            cl_int = (cl_int << 7) | 0xFF;
            first_byte = first_byte << 1;// удаляем начальную единицу в 'first_byte'
        }
        ++i; //следующий символ
    }
    return result; // возвращаем результат
}

std::string utf16_to_utf8 (std::wstring str){
    
    std::string result = ""; // начальное
    for (int i=0; i < str.length(); ++i){   // Проходим по всем символам
        uint16_t curr_char = str[i];
        if (curr_char < 0x80){              // для кодирования в utf8 нуен один байт
            result.push_back(curr_char);
        }else if (curr_char < 0x800){       // два байта
            result.push_back(0xC0 | (curr_char >> 6));
            result.push_back(0x80 | (curr_char & 0x3F));
        }else{                              // три байта
            result.push_back(0xC0 | (curr_char >> 12));
            result.push_back(0x80 | ((curr_char >> 6 )& 0x3F));
            result.push_back(0x80 | (curr_char & 0x3F));
        }
    }
    return result; //возвращаем результат
}
