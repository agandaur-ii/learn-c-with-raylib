      if (IsKeyPressed(KEY_RIGHT) && (missingPieceId + 1) % 4 != 0)
        {
          int targetPieceId = missingPieceId + 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_LEFT) && (missingPieceId) % 4 != 0)
        {
          int targetPieceId = missingPieceId - 1;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_UP) && missingPieceId - 4 > 1)
        {
          int targetPieceId = missingPieceId - 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
      else if (IsKeyPressed(KEY_DOWN) && missingPieceId + 4 < 15)
        {
          int targetPieceId = missingPieceId + 4;
          Piece temp = pieces[missingPieceId];
          pieces[missingPieceId] = pieces[targetPieceId];
          pieces[targetPieceId] = temp;
          missingPieceId = targetPieceId;
        }
