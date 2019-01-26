# configs

A repository to hold configuration files for different types of software

Some of the files I set up with a symlink on the appropriate folder linking to the files in the repository, remember to do this when setting up the config for some of the programs these configs are meant to be used with with `mklink dst src`.

# Setting it up

## System Startup

Putting a symlink to the `startup.bat` file in the startup folder of the user (check with `run -> shell:startup`).

```
mklink "%STARTUP_FOLDER%" C:\_w\kongfig\scripts\startup.bat
```

## Shell

Execute the registry changes under `kongfig\cmd`.

Make a shortcut to `cmd.exe` that calls our `shell.bat` byt putting this on the shortcut properties.

```
C:\Windows\system32\cmd.exe /k"C:\_w\kongfig\scripts\shell.bat"
```