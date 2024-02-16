import pyautogui

PATH_TO_SCBL = 'C:\SBCL\sbcl.exe'

screenWidth, screenHeight = pyautogui.size()
pyautogui.click(screenHeight - 50, screenWidth / 2)
pyautogui.write('(SB-EXT:EXIT)')
pyautogui.press('enter')
pyautogui.write(PATH_TO_SCBL)
pyautogui.press('enter')
pyautogui.write('(require "asdf")')
pyautogui.press('enter')
pyautogui.write('(asdf:load-asd (merge-pathnames "project.asd" (uiop:getcwd)))')
pyautogui.press('enter')
pyautogui.write('(asdf:load-system :project)')
pyautogui.press('enter')