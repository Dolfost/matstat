let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Lib/NAU/Mathematical_statistics/Labs/Lab/lab
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +10 main.cpp
badd +238 include/statistics/plotBase.cpp
badd +53 include/statistics/plotBase.hpp
badd +1 include/statistics/dataSeries.cpp
badd +15 include/statistics/dataSeries.hpp
badd +1 include/statistics/dataVector.hpp
badd +1 include/statistics/dataVector.cpp
badd +44 include/statistics/classSeries.cpp
badd +13 include/statistics/classSeries.hpp
badd +58 include/statistics/distributionChart.cpp
badd +13 include/statistics/distributionChart.hpp
badd +22 include/types.hpp
badd +19 include/statistics/densityChart.hpp
badd +72 include/statistics/densityChart.cpp
badd +41 include/gui/mainWindow.hpp
badd +206 include/gui/mainWindow.cpp
badd +13 CMakeLists.txt
badd +344 exprtk_cmake/readme.txt
badd +7 include/gui/Section.cpp
badd +64 include/gui/vectorContainerWidget.hpp
badd +42 include/gui/transformationFormulaEditorDialog.cpp
badd +51 include/gui/vectorPickerDialog.hpp
badd +46 include/gui/transformationFormulaEditorDialog.hpp
badd +29 include/gui/vectorPickerDialog.cpp
badd +65 include/gui/vectorContainerWidget.cpp
badd +33 include/gui/vectorInfoDialog.hpp
badd +179 include/gui/vectorInfoDialog.cpp
badd +12 include/statistics/varSeries.hpp
badd +33 include/gui/vectorProcessorWidget.hpp
badd +2 include/gui/vectorProcessorWidget.cpp
badd +5 include/gui/guiTypes.hpp
badd +1 include/gui/rangeSlider.hpp
badd +13 include/gui/vectorTrimmerDialog.hpp
badd +1 include/gui/vectorTrimmerDialog.cpp
badd +6 include/gui/rangeSlider.cpp
badd +1 include/statistics/dataVectorExprtk.hpp
badd +31 include/statistics/distributionReproducer.hpp
badd +245 include/statistics/distributionReproducer.cpp
badd +5 include/gui/distributionReproducerDialog.cpp
badd +22 include/gui/distributionReproducerDialog.hpp
badd +1 include/statistics/statistics.hpp
badd +71 include/statistics/statistics.cpp
badd +35 include/statistics/statisticsExprtk.hpp
badd +180 include/gui/setGeneratorDialog.cpp
badd +38 include/gui/setGeneratorDialog.hpp
badd +2 include/statistics/varSeries.cpp
badd +40 include/gui/plotBase.hpp
badd +1 include/statistics/dataVector/src/dataVector.cpp
badd +55 include/statistics/dataVector/dataVector.hpp
badd +1 include/statistics/dataVector/src/centralMoment.cpp
badd +19 include/statistics/dataVector/src/classSeries.cpp
badd +54 include/statistics/dataVector/src/exptrk.cpp
badd +12 include/statistics/dataVector/src/kolmConsentCriterion.cpp
badd +8 include/statistics/dataVector/src/pearConsentCriterion.cpp
badd +2 include/statistics/dataVector/src/varSeries.cpp
badd +20 include/statistics/dataVector/src/variationCoef.cpp
badd +54 include/statistics/dataVector/src/reproduceDistribution.cpp
badd +26 include/statistics/dataVector/src/transform.cpp
badd +83 include/gui/plotBase.cpp
badd +1 include/gui/densityChart.hpp
badd +32 include/gui/densityChart.cpp
badd +57 include/gui/distributionChart.cpp
argglobal
%argdel
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit main.cpp
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 10 - ((9 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 022|
tabnext
edit include/statistics/distributionReproducer.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
argglobal
balt include/statistics/distributionReproducer.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 245 - ((20 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 245
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/distributionReproducer.hpp", ":p")) | buffer include/statistics/distributionReproducer.hpp | else | edit include/statistics/distributionReproducer.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/distributionReproducer.hpp
endif
balt include/statistics/distributionReproducer.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 49 - ((12 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 49
normal! 026|
wincmd w
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
tabnext
edit include/statistics/dataVector/src/reproduceDistribution.cpp
argglobal
balt include/statistics/distributionReproducer.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 54 - ((13 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 54
normal! 010|
tabnext
edit include/statistics/dataVector/dataVector.hpp
argglobal
balt include/gui/vectorInfoDialog.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 55 - ((8 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 55
normal! 024|
tabnext
edit include/gui/vectorInfoDialog.cpp
argglobal
balt include/statistics/dataVector/dataVector.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 3 - ((2 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 3
normal! 033|
tabnext
edit include/statistics/varSeries.hpp
argglobal
balt include/statistics/classSeries.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 10 - ((9 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 0
tabnext
edit include/gui/plotBase.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
argglobal
balt include/gui/plotBase.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 89 - ((30 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 89
normal! 025|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/plotBase.hpp", ":p")) | buffer include/gui/plotBase.hpp | else | edit include/gui/plotBase.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/plotBase.hpp
endif
balt include/gui/plotBase.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 62 - ((26 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 62
normal! 021|
wincmd w
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
tabnext
edit include/gui/densityChart.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
argglobal
balt include/gui/densityChart.hpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 32 - ((26 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 32
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/densityChart.hpp", ":p")) | buffer include/gui/densityChart.hpp | else | edit include/gui/densityChart.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/densityChart.hpp
endif
balt include/gui/densityChart.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 95 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 94 + 95) / 190)
tabnext
edit include/statistics/dataVector/src/transform.cpp
argglobal
balt include/statistics/dataVector/src/exptrk.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 12 - ((11 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 12
normal! 041|
tabnext
edit include/gui/distributionChart.cpp
argglobal
balt include/gui/densityChart.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 70 - ((28 * winheight(0) + 19) / 39)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 70
normal! 033|
tabnext 3
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
