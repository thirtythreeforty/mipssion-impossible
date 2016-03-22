# This is an assembler for the MIPSsion Impossible assembly language.
# It is terrible and brittle, do not judge.

def offToHex(offset):
    assert 0 <= offset < 16
    return "%01X" % offset
def addrToHex(offset):
    return "%03X" % offset
def litToHex(lit):
    return "%01X" % (lit % 16)

def assemble(currloc, locations, line):
    opcodes = [
        'addi',
        'add',
        'sub',
        'and',
        'or',
        'xor',
        'sll',
        'srl',
        'blt',
        'j',
        'jl',
        'jr',
        'beq',
        'lw',
        'sw',
        'lbi',
    ]

    registers = [
        '$zero',
        '$v0',
        '$v1',
        '$v2',
        '$v3',
        '$t0',
        '$t1',
        '$t2',
        '$t3',
        '$a0',
        '$a1',
        '$a2',
        '$a3',
        '$13',
        '$14',
        '$15',
    ]

    def regLookup(reg):
        return offToHex(registers.index(reg))

    def joinNybbles(*n):
        return "".join(n)

    # Split line into tokens using spaces
    tokens = line.split()
    inst = tokens[0]
    opcode = offToHex(opcodes.index(inst))

    # Jump-type instructions

    if inst in ['j', 'jl']:
        loc = tokens[1]
        if loc in locations:
            return joinNybbles(opcode,
                               addrToHex(locations[loc]))
        else:
            return line

    if inst == 'jr':
        return joinNybbles(opcode, '000')

    if inst in ['srl', 'sll']:
        return joinNybbles(opcode,
                           regLookup(tokens[1]), regLookup(tokens[2]),
                           litToHex(int(tokens[3], 0)))

    if inst in ['add', 'sub', 'and', 'or', 'xor']:
        return joinNybbles(opcode,
                           regLookup(tokens[1]),
                           regLookup(tokens[2]),
                           regLookup(tokens[3]))

    # Immediate instructions
    if inst == 'addi':
        return joinNybbles(opcode,
                           litToHex(int(tokens[3], 0)),
                           regLookup(tokens[2]),
                           regLookup(tokens[1]))

    if inst == 'lbi':
        return joinNybbles(opcode,
                           "%02X" % int(tokens[2], 0),
                           regLookup(tokens[1]))

    if inst in ['blt', 'beq']:
        return joinNybbles(opcode,
                           offToHex(locations[tokens[3]] - currloc + 4),
                           regLookup(tokens[2]),
                           regLookup(tokens[1]))

    if inst in ['lw', 'sw']:
        import re
        m = re.search(r"([\d-]+)+\((.*)\)", tokens[2])
        return joinNybbles(opcode,
                           litToHex(int(m.group(1))),
                           regLookup(m.group(2)),
                           regLookup(tokens[1]))

    return line

def translate(locations, lines):
    lines = [assemble(currloc, locations, line)
        for currloc, line in enumerate(lines)]
    return lines

def filter_labels(lines):
    currloc = 0
    locations = {}
    for line in lines:
        if line.strip()[-1] == ':':
            locations[line.strip()[:-1]] = currloc
        else:
            currloc += 1

    filtered_lines = [line for line in lines if line.strip()[-1] != ':']
    return filtered_lines, locations

if __name__ == "__main__":
    import fileinput
    lines = (line.strip() for line in fileinput.input())

    def goodLine(line):
        return line != '' and line[0] != ';'

    lines = [line for line in lines if goodLine(line)]
    lines, locations = filter_labels(lines)
    tlines = translate(locations, lines)
    for linenum, (tline, line) in enumerate(zip(tlines, lines)):
        linehex = "%04X" % linenum
        bintline = '{0:016b}'.format(int(tline, 16))
        if tline == line:
            print(linehex + " " + line)
        else:
            print(linehex + " " + tline + " " + bintline + "         " + line)
