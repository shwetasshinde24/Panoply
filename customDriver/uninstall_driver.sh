service aesmd stop
/sbin/modprobe -r isgx
rm -rf "/lib/modules/"`uname -r`"/kernel/drivers/intel/sgx"
/sbin/depmod
/bin/sed -i '/^isgx$/d' /etc/modules
