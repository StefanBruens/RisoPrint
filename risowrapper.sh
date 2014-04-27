#! /bin/bash

TMPDIR=`mktemp -d`

cat > ${TMPDIR}/wtsprolog.ps <<EOF
/spot_iellipt { 
        dup mul .9 mul exch dup mul add 1 sub 
} def

/spot_rb { % another from the "Red Book"
        180 mul cos exch 180 mul cos add 2 div
} def

<< /UseWTS true >> setuserparams
/HTDefault <<
/AccurateScreens true
/HalftoneType 1
/HalftoneName (Round Dot Screen) cvn
/SpotFunction { dup mul .9 mul exch dup mul add 1 sub }
/Frequency 107
/Angle 53
>> /Halftone defineresource

/HTDefault /Halftone findresource
/Default exch /Halftone defineresource

sethalftone

<< /HalftoneMode 1 >> setuserparams
EOF

# FIXME: HWMargins, lbrt
cat > ${TMPDIR}/margins.ps <<EOF
<<  /.HWMargins [8 10 8 10] /Margins [ 0 0]  >>  setpagedevice
EOF

echo "Temp directory: $TMPDIR"
echo "Printing $@ to out.prn"

echo -n "Raster ..."
#gs -dNOPAUSE -dBATCH -r300x600 -dNORANGEPAGESIZE -sPAPERSIZE=a3 \
gs -dNOPAUSE -dBATCH -r300x600 -dNORANGEPAGESIZE \
	-sDEVICE=pbmraw -sOutputFile=${TMPDIR}/out.pbm \
	${TMPDIR}/wtsprolog.ps ${TMPDIR}/margins.ps \
	"$@" > ${TMPDIR}/gs.log
	# -sTextAlphaBits=2 -sGraphicsAlphaBits=4 \

echo "done"
echo -n "Encoding for Riso ..."

sample/risoencode -o out.prn $TMPDIR/out.pbm > ${TMPDIR}/encoder.log

echo "done"
