let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Lib/NAU/Mathematical_statistics/Labs/Lab_1
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
badd +113 include/statistics/plotBase.cpp
badd +37 include/statistics/plotBase.hpp
badd +1 include/statistics/dataSeries.cpp
badd +16 include/statistics/dataSeries.hpp
badd +138 include/statistics/dataVector.hpp
badd +748 include/statistics/dataVector.cpp
badd +61 include/statistics/classSeries.cpp
badd +4 include/statistics/classSeries.hpp
badd +75 include/statistics/distributionChart.cpp
badd +13 include/statistics/distributionChart.hpp
badd +21 include/types.hpp
badd +19 include/statistics/densityChart.hpp
badd +73 include/statistics/densityChart.cpp
badd +49 include/gui/mainWindow.hpp
badd +160 include/gui/mainWindow.cpp
badd +6 CMakeLists.txt
badd +344 exprtk_cmake/readme.txt
badd +7 include/gui/Section.cpp
badd +25 include/gui/vectorContainerWidget.hpp
badd +6 include/gui/transformationFormulaEditorDialog.cpp
badd +51 include/gui/vectorPickerDialog.hpp
badd +43 include/gui/transformationFormulaEditorDialog.hpp
badd +29 include/gui/vectorPickerDialog.cpp
badd +320 include/gui/vectorContainerWidget.cpp
badd +40 include/gui/vectorInfoDialog.hpp
badd +230 include/gui/vectorInfoDialog.cpp
badd +10 include/statistics/varSeries.hpp
badd +89 include/gui/vectorProcessorWidget.hpp
badd +79 include/gui/vectorProcessorWidget.cpp
badd +20 include/gui/guiTypes.hpp
badd +1 include/gui/rangeSlider.hpp
badd +24 include/gui/vectorTrimmerDialog.hpp
badd +1 include/gui/vectorTrimmerDialog.cpp
badd +6 include/gui/rangeSlider.cpp
badd +3 include/statistics/dataVectorExprtk.hpp
badd +46 include/statistics/distributionReproducer.hpp
badd +300 include/statistics/distributionReproducer.cpp
badd +172 include/gui/distributionReproducerDialog.cpp
badd +36 include/gui/distributionReproducerDialog.hpp
badd +1 include/statistics/statistics.hpp
badd +102 include/statistics/statistics.cpp
badd +35 include/statistics/statisticsExprtk.hpp
badd +166 include/gui/setGeneratorDialog.cpp
badd +26 include/gui/setGeneratorDialog.hpp
badd +3 include/statistics/varSeries.cpp
argglobal
%argdel
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
let s:l = 10 - ((9 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 022|
tabnext
edit include/gui/vectorProcessorWidget.cpp
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
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
argglobal
balt include/gui/vectorProcessorWidget.hpp
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
let s:l = 79 - ((11 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 79
normal! 043|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorProcessorWidget.hpp", ":p")) | buffer include/gui/vectorProcessorWidget.hpp | else | edit include/gui/vectorProcessorWidget.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorProcessorWidget.hpp
endif
balt include/gui/vectorProcessorWidget.cpp
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
let s:l = 56 - ((20 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 56
normal! 014|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
tabnext
edit include/statistics/classSeries.cpp
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
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
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
let s:l = 61 - ((18 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 61
normal! 028|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/classSeries.hpp", ":p")) | buffer include/statistics/classSeries.hpp | else | edit include/statistics/classSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/classSeries.hpp
endif
balt include/statistics/classSeries.cpp
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
let s:l = 4 - ((3 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 4
normal! 025|
wincmd w
exe 'vert 1resize ' . ((&columns * 99 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 113 + 106) / 213)
tabnext
edit include/statistics/dataVector.cpp
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
exe 'vert 1resize ' . ((&columns * 86 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 126 + 106) / 213)
argglobal
balt include/statistics/dataVector.hpp
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
let s:l = 767 - ((21 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 767
normal! 016|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/dataVector.hpp", ":p")) | buffer include/statistics/dataVector.hpp | else | edit include/statistics/dataVector.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/dataVector.hpp
endif
balt include/statistics/dataVector.cpp
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
let s:l = 157 - ((24 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 157
normal! 014|
wincmd w
exe 'vert 1resize ' . ((&columns * 86 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 126 + 106) / 213)
tabnext
edit include/statistics/varSeries.cpp
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
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
argglobal
balt include/statistics/varSeries.hpp
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
let s:l = 4 - ((3 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 4
normal! 011|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/varSeries.hpp", ":p")) | buffer include/statistics/varSeries.hpp | else | edit include/statistics/varSeries.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/varSeries.hpp
endif
balt include/statistics/varSeries.cpp
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
let s:l = 10 - ((9 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 018|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
tabnext 4
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
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
