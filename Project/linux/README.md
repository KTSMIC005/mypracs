# Linux Quick Start Guide (Ubuntu, Raspberry Pi, ...)

0. Connect your Raspberry Pi to the internet and open it's console. ^_^

1. Install WiringPi:
    http://wiringpi.com/download-and-install/

2. Download and build Blynk:
    ```bash
    $ git clone https://github.com/blynkkk/blynk-library.git
    $ cd blynk-library/linux
    $ make clean all target=raspberry
    ```

3. Run Blynk:
    ```bash
    $ sudo ./blynk --token=wR0WUwgv87bNmhupF8M7w39LhfJ9R5lF

    ```

We have also provided a build script, you can try just running (inside of the "linux" directory):

```bash
$ ./build.sh raspberry
```
