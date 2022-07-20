
# Building

*How to compile this mod.*

<br>

## Dependencies

[<kbd>  AutoTOML  </kbd>][AutoTOML]  
[<kbd>  CommonLibSSE  </kbd>][CommonLibSSE]  
[<kbd>  SpdLog  </kbd>][SpdLog]

<br>
<br>

## Building

1.  Clone the repository:
    
    ```shell
    git clone https://github.com/mlthelama/ShowStats.git
    ```
    
2.  Navigate to the root folder:

    ```shell
    cd ShowStats
    ```
    
3.  Clone the submodules:

    ```shell
    git submodule update --init --recursive
    ```
    
4.  Compile the code:

    ```
    cmake -B build -S .
    ```

<br>


<!----------------------------------------------------------------------------->

[CommonLibSSE]: https://github.com/Ryan-rsm-McKenzie/CommonLibSSE
[AutoTOML]: https://github.com/Ryan-rsm-McKenzie/AutoTOML
[SpdLog]: https://github.com/gabime/spdlog
