import os
import string

class VirtualMachine:
    def __init__(self, instruction):
        self.instruction = instruction
        self.stack = list()
        self.instruction_line = list()
        self.addr = 0
        self.dispatch_map_of_two_arg={}
        self.dispatch_map_of_no_arg = {
            # "%":        self.mod,
            # "*":        self.mul,
            # "+":        self.plus,
            # "-":        self.minus,
            # "/":        self.div,
            # "==":       self.eq,
            # "cast_int": self.cast_int,
            # "cast_str": self.cast_str,
            # "drop":     self.drop,
            # "dup":      self.dup,
            # "over":     self.over,
            # "println":  self.println,
            # "04":       self.read,

            "00":       self.nop,
            "01":       self.printf,
            "02":       self.if_stmt,
            "03":       self.jmp,
            "05":       self.swap,

            "16":    self.dump_stack,

            "FF":     self.exit_with_code,
        }
        self.dispatch_map_of_one_arg = {
            "06":       self.push
        }
    def getinstruction(self):
        sentinel = 'end main'
        for instruction in iter(input, sentinel):
            self.instruction_line.append(instruction)

    def nop():
        return

    def decoder(self, instruction_line):
            dispatch(instruction_line)

    def dump_stack(self):
        for contain in self.stack:
            print(contain)
            print("\n")

    def push(self, value):
        return self.stack.append(value)

    def pop(self):
        return self.stack.pop()

    def printf(self):
        result=""
        while(self.top()):
            result+=self.ASCII_decoder()
        print(''.join(reversed(result)))
        return len(result)

    def top(self):
        return self.stack[-1]

    def jmp(self):
        position=self.pop()
        if (0 <= position <= self.len(instruction_line) and isinstance(position, int)):
            self.addr = position
            return 0
        elif(not isinstance(position, int)):
            raise "jmp position must be Integer"
        else:
            raise "over jmp!"

    def if_stmt(self):
        if(pop() == pop()):
            return True
        else:
            return False
    
    def swap(self):
        a=self.pop()
        b=self.pop()
        self.push(a)
        self.push(b)

    def ASCII_decoder(self):
        opcode=self.pop()
        if(opcode == 0):
            return False
        elif(opcode ==100):
            return '_'
        elif(opcode <= 26):
            return string.ascii_uppercase[opcode-1]
        elif(opcode >= 27):
            return string.ascii_lowercase[opcode-27]
        

    def exit_with_code(self):
        exit(self.pop())

    def dispatch(self):
        opcode=self.instruction
        
        if  opcode[self.addr] in self.dispatch_map_of_no_arg:
            result=self.dispatch_map_of_no_arg[opcode[self.addr]]()
            self.addr+=1
            return result
        elif opcode[self.addr] in  self.dispatch_map_of_one_arg:
            result=self.dispatch_map_of_one_arg[opcode[self.addr]](opcode[self.addr+1])
            self.addr+=2
            return result
        elif opcode[self.addr] in  self.dispatch_map_of_two_arg:
            result = self.dispatch_map_of_two_arg[opcode[self.addr]](opcode[self.addr+1],opcode[self.addr+2])
            self.addr+=3
            return result

if __name__ == '__main__':
    instructionlist=['06',00,'06', 34, '06', 27, '06', 48, '06', 31, '06', 100, '06', 32, '06', 47, '06', 40, 
                    '06', 100, '06', 49, '06', 35, '06', 46, '06', 34, '06', 100, '06', 22, '06', 13,"01"]
    myVM=VirtualMachine(instructionlist)
    while(myVM.addr<len(instructionlist)):  
        myVM.dispatch()
