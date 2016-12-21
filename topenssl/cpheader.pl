#!/usr/bin/perl

use File::Basename;
my $SRC="ssl/dtls1.h ssl/kssl.h ssl/srtp.h ssl/ssl23.h ssl/ssl2.h ssl/ssl3.h ssl/ssl.h ssl/tls1.h crypto/cmac/cmac.h crypto/srp/srp.h crypto/ts/ts.h crypto/pqueue/pqueue.h crypto/cms/cms.h crypto/krb5/krb5_asn.h crypto/ui/ui_compat.h crypto/ui/ui.h crypto/ocsp/ocsp.h crypto/comp/comp.h crypto/pkcs12/pkcs12.h crypto/pkcs7/pkcs7.h crypto/txt_db/txt_db.h crypto/conf/conf_api.h crypto/conf/conf.h crypto/x509v3/x509v3.h crypto/x509/x509.h crypto/x509/x509_vfy.h crypto/pem/pem2.h crypto/pem/pem.h crypto/asn1/asn1.h crypto/asn1/asn1_mac.h crypto/asn1/asn1t.h crypto/evp/evp.h crypto/err/err.h crypto/rand/rand.h crypto/lhash/lhash.h crypto/stack/safestack.h crypto/stack/stack.h crypto/bio/bio.h crypto/buffer/buffer.h crypto/engine/engine.h crypto/dso/dso.h crypto/ecdh/ecdh.h crypto/dh/dh.h crypto/ecdsa/ecdsa.h crypto/dsa/dsa.h crypto/rsa/rsa.h crypto/ec/ec.h crypto/bn/bn.h crypto/modes/modes.h crypto/seed/seed.h crypto/camellia/camellia.h crypto/cast/cast.h crypto/bf/blowfish.h crypto/idea/idea.h crypto/rc4/rc4.h crypto/rc2/rc2.h crypto/aes/aes.h crypto/des/des.h crypto/des/des_old.h crypto/whrlpool/whrlpool.h crypto/ripemd/ripemd.h crypto/hmac/hmac.h crypto/mdc2/mdc2.h crypto/sha/sha.h crypto/md5/md5.h crypto/md4/md4.h crypto/objects/objects.h crypto/objects/obj_mac.h crypto/crypto.h crypto/ebcdic.h crypto/opensslconf.h crypto/opensslv.h crypto/ossl_typ.h crypto/symhacks.h e_os2.h crypto/store/store.h crypto/md2/md2.h";
my @file_list = split(/ /,$SRC);
foreach $file (@file_list){
    my $target = "include/openssl/".basename($file);
    open (OLD, "<$file") or die("Can't open file $file: $!");
    open (NEW, ">$target") or die("Can't create file $target: $!");
    binmode(OLD);
    binmode(NEW);
    while (<OLD>){
        print NEW $_;
    }
    close (OLD) or die "Can't close $file: $!";
    close (NEW) or die "Can't close $target: $!";
}

