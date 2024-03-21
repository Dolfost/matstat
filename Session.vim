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
badd +1 main.cpp
badd +266 include/statistics/plotBase.cpp
badd +40 include/statistics/plotBase.hpp
badd +1 include/statistics/dataSeries.cpp
badd +16 include/statistics/dataSeries.hpp
badd +99 include/statistics/dataVector.hpp
badd +1 include/statistics/dataVector.cpp
badd +53 include/statistics/classSeries.cpp
badd +23 include/statistics/classSeries.hpp
badd +68 include/statistics/distributionChart.cpp
badd +13 include/statistics/distributionChart.hpp
badd +21 include/types.hpp
badd +16 include/statistics/densityChart.hpp
badd +12 include/statistics/densityChart.cpp
badd +1 include/gui/mainWindow.hpp
badd +142 include/gui/mainWindow.cpp
badd +21 CMakeLists.txt
badd +340 exprtk_cmake/readme.txt
badd +7 include/gui/Section.cpp
badd +33 include/gui/vectorContainerWidget.hpp
badd +6 include/gui/transformationFormulaEditorDialog.cpp
badd +51 include/gui/vectorPickerDialog.hpp
badd +36 include/gui/transformationFormulaEditorDialog.hpp
badd +29 include/gui/vectorPickerDialog.cpp
badd +1 include/gui/vectorContainerWidget.cpp
badd +40 include/gui/vectorInfoDialog.hpp
badd +29 include/gui/vectorInfoDialog.cpp
badd +18 include/statistics/varSeries.hpp
badd +37 include/gui/vectorProcessorWidget.hpp
badd +60 include/gui/vectorProcessorWidget.cpp
badd +1 include/gui/guiTypes.hpp
badd +1 include/gui/rangeSlider.hpp
badd +24 include/gui/vectorTrimmerDialog.hpp
badd +1 include/gui/vectorTrimmerDialog.cpp
badd +6 include/gui/rangeSlider.cpp
badd +3 include/statistics/dataVectorExprtk.hpp
badd +35 include/statistics/distributionReproducer.hpp
badd +289 include/statistics/distributionReproducer.cpp
badd +150 include/gui/distributionReproducerDialog.cpp
badd +10 include/gui/distributionReproducerDialog.hpp
badd +22 include/statistics/statistics.hpp
badd +78 include/statistics/statistics.cpp
badd +35 include/statistics/statisticsExprtk.hpp
badd +119 include/gui/setGeneratorDialog.cpp
badd +26 include/gui/setGeneratorDialog.hpp
argglobal
%argdel
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
let s:l = 5 - ((3 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5
normal! 0
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
exe 'vert 1resize ' . ((&columns * 105 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 84 + 95) / 190)
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
let s:l = 478 - ((18 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 478
normal! 09|
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
let s:l = 30 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 30
normal! 027|
wincmd w
exe 'vert 1resize ' . ((&columns * 105 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 84 + 95) / 190)
tabnext
edit include/gui/setGeneratorDialog.cpp
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
exe 'vert 1resize ' . ((&columns * 110 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 79 + 95) / 190)
argglobal
balt include/gui/setGeneratorDialog.hpp
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
let s:l = 120 - ((27 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 120
normal! 012|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/setGeneratorDialog.hpp", ":p")) | buffer include/gui/setGeneratorDialog.hpp | else | edit include/gui/setGeneratorDialog.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/setGeneratorDialog.hpp
endif
balt include/gui/setGeneratorDialog.cpp
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
let s:l = 26 - ((25 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 26
normal! 026|
wincmd w
exe 'vert 1resize ' . ((&columns * 110 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 79 + 95) / 190)
tabnext
edit include/gui/vectorContainerWidget.cpp
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
exe 'vert 1resize ' . ((&columns * 94 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 95 + 95) / 190)
argglobal
balt include/gui/vectorContainerWidget.hpp
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
let s:l = 308 - ((25 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 308
normal! 054|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/vectorContainerWidget.hpp", ":p")) | buffer include/gui/vectorContainerWidget.hpp | else | edit include/gui/vectorContainerWidget.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/vectorContainerWidget.hpp
endif
balt include/gui/vectorContainerWidget.cpp
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
let s:l = 33 - ((15 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 05|
wincmd w
exe 'vert 1resize ' . ((&columns * 94 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 95 + 95) / 190)
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
exe 'vert 1resize ' . ((&columns * 102 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 87 + 95) / 190)
argglobal
balt main.cpp
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
let s:l = 289 - ((11 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 289
normal! 049|
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/distributionReproducer.hpp", ":p")) | buffer include/statistics/distributionReproducer.hpp | else | edit include/statistics/distributionReproducer.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/distributionReproducer.hpp
endif
balt include/gui/distributionReproducerDialog.hpp
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
let s:l = 35 - ((26 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 35
normal! 064|
wincmd w
exe 'vert 1resize ' . ((&columns * 102 + 95) / 190)
exe 'vert 2resize ' . ((&columns * 87 + 95) / 190)
tabnext
edit include/gui/mainWindow.cpp
argglobal
balt include/gui/vectorContainerWidget.cpp
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
let s:l = 142 - ((18 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 142
normal! 070|
tabnext 5
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
