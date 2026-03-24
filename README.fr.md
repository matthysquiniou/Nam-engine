# NAM Engine

Moteur de jeu C++ personnalisé utilisant **DirectX 12**, avec une architecture **Entity‑Component‑System (ECS)**, un pipeline de rendu flexible, une physique intégrée avec détection de collisions, des effets de particules, des composants UI et des outils de génération procédurale.

---

## Installation et Génération de la Solution

1. Allez dans le dossier `bin/`.
2. Exécutez `make.bat`.
3. Le script générera un dossier `ide/` contenant `nam_engine.sln`.
4. Ouvrez la solution Visual Studio.

---

## Fonctionnalités

### Entity‑Component‑System (ECS)
- **Stockage type‑sécurisé** des composants grâce à des sparse sets paginés pour une efficacité cache.
- **Requêtes rapides** via des vues templatées qui se rafraîchissent automatiquement lors de l’ajout/suppression d’entités.
- **Systèmes** (rendu, physique, UI…) activables/désactivables individuellement.
- **Wrapper `GameObject`** qui simplifie l’utilisation de l’ECS dans le code gameplay.

### Rendu (DirectX 12)
- **Rendu 3D** avec textures diffuses et plusieurs types de lumières (directionnelle, ponctuelle, spot).
- **Rendu 2D** pour sprites et textes avec alpha blending et ordre de dessin personnalisé.
- **Système de particules GPU** utilisant des compute shaders (mise à jour, génération, affichage).
- **Matériau albedo uniquement** (pas de système de matériaux complet – seulement l’ombrage diffus basique).

### Physique & Collisions
- **Boîtes englobantes alignées sur les axes (AABB)** et **boîtes orientées (OBB)**.
- **Colliders sphériques** et **colliders cubiques** avec étendues basées sur le mesh ou personnalisées.
- **Table de hachage spatiale** pour une détection large‑phase efficace.
- **Réponse basée sur l’impulsion** avec masse et restitution.
- **Gravité** et **intégration de la vitesse** pour les corps rigides.

### UI
- **Composants bouton** avec événements survol, clic et sortie.
- **Système UI** qui gère l’interaction souris avec les sprites rotatifs.
- **Rendu de texte** avec crénage personnalisé, jeux de caractères et couches de dessin.

### Génération Procédurale
- **Bruit de Perlin** pour la génération de terrain / heightmap.
- **Échantillonnage de Poisson** pour des points aléatoires bien répartis.
- **Grille de voxels** (sphère, boîte, évolution par trou) et extraction de maillage.

---

## Dépendances

- **Windows SDK** (pour DirectX 12)
- **DirectX 12** (D3D12, DXGI, D3DCompiler)
- **Compilateur C++17** (ou plus récent) – testé avec MSVC
