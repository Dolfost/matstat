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
badd +41 include/statistics/classSeries.cpp
badd +13 include/statistics/classSeries.hpp
badd +58 include/statistics/distributionChart.cpp
badd +13 include/statistics/distributionChart.hpp
badd +22 include/types.hpp
badd +19 include/statistics/densityChart.hpp
badd +72 include/statistics/densityChart.cpp
badd +53 include/gui/mainWindow.hpp
badd +1 include/gui/mainWindow.cpp
badd +13 CMakeLists.txt
badd +344 exprtk_cmake/readme.txt
badd +7 include/gui/Section.cpp
badd +64 include/gui/vectorContainerWidget.hpp
badd +75 include/gui/transformationFormulaEditorDialog.cpp
badd +51 include/gui/vectorPickerDialog.hpp
badd +24 include/gui/transformationFormulaEditorDialog.hpp
badd +29 include/gui/vectorPickerDialog.cpp
badd +1 include/gui/vectorContainerWidget.cpp
badd +1 include/gui/vectorInfoDialog.hpp
badd +38 include/gui/vectorInfoDialog.cpp
badd +10 include/statistics/varSeries.hpp
badd +13 include/gui/vectorProcessorWidget.hpp
badd +98 include/gui/vectorProcessorWidget.cpp
badd +1 include/gui/guiTypes.hpp
badd +1 include/gui/rangeSlider.hpp
badd +13 include/gui/vectorTrimmerDialog.hpp
badd +1 include/gui/vectorTrimmerDialog.cpp
badd +6 include/gui/rangeSlider.cpp
badd +1 include/statistics/dataVectorExprtk.hpp
badd +35 include/statistics/distributionReproducer.hpp
badd +197 include/statistics/distributionReproducer.cpp
badd +10 include/gui/distributionReproducerDialog.cpp
badd +44 include/gui/distributionReproducerDialog.hpp
badd +1 include/statistics/statistics.hpp
badd +48 include/statistics/statistics.cpp
badd +35 include/statistics/statisticsExprtk.hpp
badd +40 include/gui/setGeneratorDialog.cpp
badd +18 include/gui/setGeneratorDialog.hpp
badd +2 include/statistics/varSeries.cpp
badd +44 include/gui/plotBase.hpp
badd +1 include/statistics/dataVector/src/dataVector.cpp
badd +133 include/statistics/dataVector/dataVector.hpp
badd +1 include/statistics/dataVector/src/centralMoment.cpp
badd +19 include/statistics/dataVector/src/classSeries.cpp
badd +54 include/statistics/dataVector/src/exptrk.cpp
badd +43 include/statistics/dataVector/src/kolmConsentCriterion.cpp
badd +18 include/statistics/dataVector/src/pearConsentCriterion.cpp
badd +2 include/statistics/dataVector/src/varSeries.cpp
badd +20 include/statistics/dataVector/src/variationCoef.cpp
badd +1 include/statistics/dataVector/src/reproduceDistribution.cpp
badd +12 include/statistics/dataVector/src/transform.cpp
badd +148 include/gui/plotBase.cpp
badd +1 include/gui/densityChart.hpp
badd +32 include/gui/densityChart.cpp
badd +57 include/gui/distributionChart.cpp
badd +9 include/statistics/dataVector/src/cdf.cpp
badd +2034 include/QCustomPlot/qcustomplot.h
badd +7777 include/QCustomPlot/qcustomplot.cpp
badd +52 include/gui/axisTickerExp.cpp
badd +1 include/gui/axisTickerExp.hpp
badd +10 include/gui/distributionChart.hpp
badd +17 include/statistics/dataVector/src/skewDeviation.cpp
badd +186 include/gui/charts.cpp
badd +26 include/gui/charts.hpp
badd +1 include/statistics/dataVectorSet.cpp
badd +9 include/statistics/dataVectorSet.hpp
badd +1 include/gui/hypothesisManagerDialog.cpp
badd +39 include/gui/hypothesisManagerDialog.hpp
argglobal
%argdel
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
let s:l = 1 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 022|
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
let s:l = 73 - ((15 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 73
normal! 023|
tabnext
edit include/statistics/dataVectorSet.cpp
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
exe 'vert 1resize ' . ((&columns * 102 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 110 + 106) / 213)
argglobal
balt include/statistics/dataVectorSet.hpp
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
let s:l = 29 - ((22 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 29
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/statistics/dataVectorSet.hpp", ":p")) | buffer include/statistics/dataVectorSet.hpp | else | edit include/statistics/dataVectorSet.hpp | endif
if &buftype ==# 'terminal'
  silent file include/statistics/dataVectorSet.hpp
endif
balt include/statistics/dataVectorSet.cpp
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
let s:l = 13 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 13
normal! 020|
wincmd w
exe 'vert 1resize ' . ((&columns * 102 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 110 + 106) / 213)
tabnext
edit include/gui/mainWindow.cpp
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
exe 'vert 1resize ' . ((&columns * 114 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 98 + 106) / 213)
argglobal
balt include/gui/mainWindow.hpp
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
let s:l = 28 - ((27 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/mainWindow.hpp", ":p")) | buffer include/gui/mainWindow.hpp | else | edit include/gui/mainWindow.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/mainWindow.hpp
endif
balt include/gui/mainWindow.cpp
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
let s:l = 53 - ((0 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 53
normal! 013|
wincmd w
exe 'vert 1resize ' . ((&columns * 114 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 98 + 106) / 213)
tabnext
edit include/gui/charts.cpp
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
exe 'vert 1resize ' . ((&columns * 96 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 116 + 106) / 213)
argglobal
balt include/gui/charts.hpp
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
let s:l = 5 - ((4 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5
normal! 04|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/charts.hpp", ":p")) | buffer include/gui/charts.hpp | else | edit include/gui/charts.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/charts.hpp
endif
balt include/gui/charts.cpp
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
let s:l = 28 - ((27 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 96 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 116 + 106) / 213)
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
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
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
let s:l = 225 - ((27 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 225
normal! 010|
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
let s:l = 38 - ((14 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 38
normal! 029|
wincmd w
exe 'vert 1resize ' . ((&columns * 106 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 106 + 106) / 213)
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
exe 'vert 1resize ' . ((&columns * 109 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 103 + 106) / 213)
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
let s:l = 381 - ((20 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 381
normal! 0
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
let s:l = 66 - ((23 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 08|
wincmd w
exe 'vert 1resize ' . ((&columns * 109 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 103 + 106) / 213)
tabnext
edit include/gui/hypothesisManagerDialog.cpp
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
exe 'vert 1resize ' . ((&columns * 118 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 94 + 106) / 213)
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
let s:l = 62 - ((20 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 62
normal! 060|
wincmd w
argglobal
if bufexists(fnamemodify("include/gui/hypothesisManagerDialog.hpp", ":p")) | buffer include/gui/hypothesisManagerDialog.hpp | else | edit include/gui/hypothesisManagerDialog.hpp | endif
if &buftype ==# 'terminal'
  silent file include/gui/hypothesisManagerDialog.hpp
endif
balt include/gui/hypothesisManagerDialog.cpp
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
let s:l = 28 - ((18 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 28
normal! 05|
wincmd w
exe 'vert 1resize ' . ((&columns * 118 + 106) / 213)
exe 'vert 2resize ' . ((&columns * 94 + 106) / 213)
tabnext 6
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
