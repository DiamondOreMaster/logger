# logger
A simple c++20 logging header file.

An example without logging the time.

![image](https://github.com/DiamondOreMaster/logger/assets/102474184/d04fb41c-66ff-48be-8db5-ad8ad2a6371f)

An example using time logging, US time format and then international time format.
![image](https://github.com/DiamondOreMaster/logger/assets/102474184/e5beb58d-ce98-4a5d-b62c-75b17a97575a)
![image](https://github.com/DiamondOreMaster/logger/assets/102474184/0f884820-0c7f-46c0-b5b9-58669365bf94)

<h1>Implementations</h1>

<h3>Without date logging</h3>

```
#include "logger.hpp"

int main() {
    logger::ERROR("This is an example of an error!");
    logger::WARN("This is an example of a warning!");
    logger::SUCCESS("This is an example of a success!");
    logger::LOG("This is an example of a log!");

    return 0;
}
```

<h3>Using US date format</h3>

```
#define LOG_TIME
#include "logger.hpp"

int main() {
    logger::ERROR("This is an example of an error!");
    logger::WARN("This is an example of a warning!");
    logger::SUCCESS("This is an example of a success!");
    logger::LOG("This is an example of a log!");

    return 0;
}
```

<h3>Using internation date format</h3>

```
#define LOG_TIME
#define INTERNATIONAL_DATE
#include "logger.hpp"

int main() {
    logger::ERROR("This is an example of an error!");
    logger::WARN("This is an example of a warning!");
    logger::SUCCESS("This is an example of a success!");
    logger::LOG("This is an example of a log!");

    return 0;
}
```
