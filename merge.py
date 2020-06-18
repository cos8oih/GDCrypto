headers = [
    'Export.hpp',
    'Keys.hpp',
    'Salts.hpp',
    'RobTopCipher.hpp',
    'DataCipher.hpp',
    'CheckGenerator.hpp'
]

includes = [
    'vector',
    'string',
    'iostream'
]

#Helpers

def findHeaderBegin(lines):
    for i in range(len(lines)):
        if lines[i].startswith('namespace gdcrypto'):
            return i + 2
    
    return 0

def findHeaderEnd(lines):
    for i in range(len(lines)):
        if lines[i] == '}':
            return i

    return 0

out = open('Include/GDCrypto.hpp', 'w')

#Write license

license = open('LICENSE', 'r').read().split('\n')

out.write('/*')

for line in license:
    if (len(line)):
        out.write('\n' + '    ' + line)

out.write('\n*/\n')

#Write file guard start

out.write('#ifndef _GDCRYPTO_HPP\n')
out.write('#define _GDCRYPTO_HPP\n\n')

#Write includes

for include in includes:
    out.write('#include <' + include + '>\n')

out.write('\n')

#Merge includes

out.write('namespace gdcrypto\n')
out.write('{')

for header in headers:
    file = open('Include/GDCrypto/' + header, 'r').read().split('\n')
    headerBegin = findHeaderBegin(file)
    headerEnd = findHeaderEnd(file)

    if (headerBegin and headerEnd):
        for i in range(headerBegin, headerEnd):
            out.write('\n' + file[i])
    else: raise Exception("Invalid header")

    out.write('\n')

out.write('}\n\n')

#Write file guard end

out.write('#endif /* _GDCRYPTO_HPP */')

out.close()