import Parser from 'tree-sitter';
import PGN from 'tree-sitter-pgn';

// Initialisation du parser avec la grammaire PGN
const parser = new Parser();
parser.setLanguage(PGN);

// Le PGN brut à parser
const pgnData = `
1.e4 e5 2.f4 exf4 {u6EBVqDGfPWDYs78S0GEJQv6yyyeEICagHEosPsjY0jMwXX57HvtE/l28JrACUyfCvD6fRNxN3YxenEYd/G9pWJDFmR2EPSA6x06xLwQ0QSqe2kdm3Oz+3RphXwvipHZCC9PE/sQ3tsWebMHFn2x8/NkLFpDURva+tWGaLdiu/5O7CzbUxOywb3AXFhthpknjGkQ776HOIYnRj40Pst6ZhnXLfncbBYkWhcQPqAsGEmi9D3WV8GSfac36oCN6L7MD3zi/n8QUaEeJvlBVF6zgjGjq+MQ03YQWqORsOl1I+xhR/sQqU1bCQylxC1CfHAxqgDGYhxowdc7+m+MkWEWjwQqj0kvPLQtcDT3K+8HYtCqe2kdm3Oz+3RphXwvipHZGPfEJyOOP2wBzwByyr6aqTwApdFx4G33jlIvPy1F0ZGqAMZiHGjB1zv6b4yRYRaPTHBPCKipbvD19tk04s1MSaoAxmIcaMHXO/pvjJFhFo+l2rXFq17IHxihKsqER7s2QdshHttUvqaMRwVW51O99qoAxmIcaMHXO/pvjJFhFo9McE8IqKlu8PX22TTizUxJlAdii/dzeTiPeEaPclPbPY02UJ0w/tGDkaf2pdsayHuUB2KL93N5OI94Ro9yU9s9GPfEJyOOP2wBzwByyr6aqZd65Se4C2hV7u6HA+NAJwICMJbBLu4YXKz+SPXGxOtsTHBPCKipbvD19tk04s1MSZQHYov3c3k4j3hGj3JT2z3WKbcXfJx1hUlyqaOgfojrl3rlJ7gLaFXu7ocD40AnAgIwlsEu7hhcrP5I9cbE62yNNlCdMP7Rg5Gn9qXbGsh7qgDGYhxowdc7+m+MkWEWjwQqj0kvPLQtcDT3K+8HYtCqe2kdm3Oz+3RphXwvipHZGPfEJyOOP2wBzwByyr6aqZd65Se4C2hV7u6HA+NAJwICMJbBLu4YXKz+SPXGxOts2X/1oaL8rF/Zgl/X5oMGwlxT+F2NbU3FwtJL4coD09oVjkESAfflqPz/r+wmnhBfN4bGVNr1nAWtoVd9+ObA8/kyppy+dvd5O8vhe+Auuk+MaRDvvoc4hidGPjQ+y3pmGdct+dxsFiRaFxA+oCwYSaL0PdZXwZJ9pzfqgI3ovswxo6vjENN2EFqjkbDpdSPsMaOr4xDTdhBao5Gw6XUj7I7GDAyVWJ38CotBSZXSGxNPVxJJ1f6pa+9N1XUatsU3MJuUhDl9/o2iiADmsJP/LA==} 3.Bc4 Qh4+ 4.Kf1 b5 5.Bxb5 Nf6 6.Nf3 Qh6
7.d3 Nh5 8.Nh4 Qg5 9.Nf5 c6 10.g4 Nf6 11.Rg1 cxb5 12.h4 Qg6
13.h5 Qg5 14.Qf3 Ng8 15.Bxf4 Qf6 16.Nc3 Bc5 17.Nd5 Qxb2 18.Bd6
Bxg1 {sgYkr46C73SDT3KwXr/Mmg==} 19. e5 Qxa1+ 20. Ke2 Na6 21.Nxg7+ Kd8 {7p/cMgz2+z8S8h7uLT36V6aTkZk9eLdRyIu+NQx4plthocAtoAf2wRnnKdEE31W2/YMJ8fZKflzmxqLFPzOu8nufVNeWk2iioC0oeXC2OiVrtzWXIT7ersmiLo/LSjgGeXCETijdKXSZqaBIVAieGrODJPPvj9Gnt+PODUBLPBkUiTtV6PbM028h6LI9Ir0bjn5LD5lIF9kS1upsvxabeMjStpcE+Boc3OgCCPfdN2qvZtPYoPuoUFpjP+ULyYBZ} 22.Qf6+ Nxf6
23.Be7#
`;

// Generer l'Arbre Syntaxique Abstrait (AST)
const tree = parser.parse(pgnData);

// 1. Affiche l'arbre complet au format S-expression
console.log("=== Structure AST brute ===");
console.log(tree.rootNode.toString());

// 2. Fonction utilitaire pour extraire les coups et les commentaires
function extractElements(node) {
  for (let i = 0; i < node.childCount; i++) {
    const child = node.child(i);
    
    // Extrait les coups en notation SAN
    if (child.type === 'san_move') {
      console.log(`Coup trouvé : ${child.text}`);
    }
    
    // Extrait les blocs de commentaires
    if (child.type === 'comment') {
      console.log(`Commentaire trouvé : ${child.text.trim()}`);
    }

    // Parcours récursif pour explorer tout le fichier
    extractElements(child);
  }
}

console.log("\n=== Éléments extraits ===");
extractElements(tree.rootNode);
