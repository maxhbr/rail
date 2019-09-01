((nil . ((intent-tabs-mode . nil)))
 (c++-mode . ((c-basic-offset . 4)
              (tab-width . 4)
              (c-file-style . "linux")
              (flycheck-clang-args . ("-nostdinc" "-nostdinc++" "-nostdlib" "-nostdlib++"))
              (eval . (setq flycheck-clang-include-path
                            (append (split-string (shell-command-to-string
                                                   (format "%s %s"
                                                           "python3 -c \"
import json
import sys
dat = json.load(open(sys.argv[1]))
print('\\n'.join(dat['configurations'][1]['includePath']))\""
                                                           (expand-file-name
                                                            (concat (projectile-project-root)
                                                                    "code/rail/.vscode/c_cpp_properties.json")))))
                                    (mapcar 'expand-file-name
                                            '("~/.platformio/packages/toolchain-xtensa32/bin/../lib/gcc/xtensa-esp32-elf/5.2.0/include"
                                              "~/.platformio/packages/toolchain-xtensa32/bin/../lib/gcc/xtensa-esp32-elf/5.2.0/include-fixed"
                                              "~/.platformio/packages/toolchain-xtensa32/bin/../lib/gcc/xtensa-esp32-elf/5.2.0/../../../../xtensa-esp32-elf/include"
                                              "~/.platformio/packages/toolchain-xtensa32/bin/../xtensa-esp32-elf/sysroot/usr/include"
                                              "~/.platformio/packages/toolchain-xtensa32/xtensa-esp32-elf/include/c++/5.2.0"
                                              "~/.platformio/packages/toolchain-xtensa32/xtensa-esp32-elf/include/c++/5.2.0/xtensa-esp32-elf")))))))
 (c-mode . ((c-basic-offset . 4)
            (tab-width . 4)
            (c-c++-default-mode-for-headers 'c++-mode)
            (c-file-style . "linux"))))
