# # This is a sample Python script.
#
# # Press ⌃R to execute it or replace it with your code.
# # Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.
#
#
# def print_hi(name):
#     # Use a breakpoint in the code line below to debug your script.
#     print(f'Hi, {name}')  # Press ⌘F8 to toggle the breakpoint.
#
#
# # Press the green button in the gutter to run the script.
# if __name__ == '__main__':
#     print_hi('PyCharm')
#
# # See PyCharm help at https://www.jetbrains.com/help/pycharm/

# def reversed1(variable):
#     res = ''
#     for i in range(len(variable)-1,-1,-1):
#         res += variable[i]
#     return res

if __name__ == '__main__':
    # n = reversed1(input())
    # print(n)
    n = input()[::-1]
    print(n)
